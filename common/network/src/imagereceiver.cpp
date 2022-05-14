/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imagereceiver.h>

#include <constants.h>
#include <common.h>
#include <utilities.h>

using namespace std;

ImageReceiver::ImageReceiver(QObject *parent)
    : IImageReceiver(parent), m_mat(SCALED_IMAGE_HEIGHT, SCALED_IMAGE_WIDTH, CV_8UC3)
{
    connect(&m_socket, &QAbstractSocket::readyRead, this, &ImageReceiver::readFrames);

    connect(&m_socket, &QAbstractSocket::stateChanged, this, [this](auto state) {
        qDebug() << "Socket state changed:" << state;
    });
}

ImageReceiver::~ImageReceiver()
{
    ImageReceiver::stop();
}

bool ImageReceiver::start(uint16_t port)
{
    if (m_running)
        return false;

    if (m_socket.bind(port)) {
        m_timer.start();
        m_running = true;
    }
    return m_running;
}

void ImageReceiver::stop()
{
    if (!m_running)
        return;

    m_socket.disconnectFromHost();
    m_running = false;
}

void ImageReceiver::readFrames()
{
    array<char, datagramSize(SCALED_IMAGE_WIDTH)> buffer;
    if (m_socket.readDatagram(buffer.data(), buffer.size()) < 0) {
        qWarning() << "Couldn't read datagram - discarded";
        return;
    }

    auto offsetPtr = buffer.data();
    auto sequence = *reinterpret_cast<SequenceType *>(offsetPtr);
    offsetPtr += SEQUENCE_SIZE;
    if (sequence < m_sequence) {
        qWarning() << "Dropped line since sequence is lagging";
        return;
    }

    if (sequence > m_sequence) {
        emit receivedFrame(
            make_shared<Frame>(m_sequence, framerateFromMs(m_timer.restart()), m_mat.clone()));
        m_sequence = sequence;
    }

    auto row = *reinterpret_cast<RowType *>(offsetPtr);
    offsetPtr += ROW_SIZE;
    if (row >= SCALED_IMAGE_HEIGHT) {
        qWarning() << "Invalid row number" << row << "Dropping line";
        return;
    }

    auto lineCount = *reinterpret_cast<RowType *>(offsetPtr);
    offsetPtr += LINE_COUNT_SIZE;
    if (lineCount > linesSent(SCALED_IMAGE_WIDTH)) {
        qWarning() << "Invalid line count" << lineCount << "Dropping line";
        return;
    }

    for (auto i = 0; i < lineCount; ++i) {
        memcpy(reinterpret_cast<char *>(m_mat.row(row + i).data),
               offsetPtr,
               lineSize(SCALED_IMAGE_WIDTH));
        offsetPtr += lineSize(SCALED_IMAGE_WIDTH);
    }
}
