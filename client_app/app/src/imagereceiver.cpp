/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imagereceiver.h>

#include <QHostAddress>

#include <common.h>

using namespace std;
using namespace cv;

ImageReceiver::ImageReceiver(QObject *parent)
    : QObject{parent}, m_image(SCALED_IMAGE_WIDTH, SCALED_IMAGE_HEIGHT, QImage::Format_BGR888)
{
    connect(&m_socket, &QAbstractSocket::readyRead, this, &ImageReceiver::readFrames);
}

void ImageReceiver::start()
{
    m_socket.bind(QHostAddress::Any, PORT);
    qDebug() << "Socket bound to" << m_socket.peerAddress() << "with port" << m_socket.peerPort();
    m_timer.start();
}

void ImageReceiver::readFrames()
{
    array<char, DATAGRAM_SIZE> buffer;
    m_socket.readDatagram(buffer.data(), buffer.size());
    //    qDebug() << (m_bytesRead += DATAGRAM_SIZE) / m_timer.elapsed() << "bytes per ms";

    auto offsetPtr = buffer.data();
    auto sequence = *reinterpret_cast<SequenceType *>(offsetPtr);
    offsetPtr += SEQUENCE_SIZE;
    if (sequence < m_sequence) {
        qWarning() << "Dropped line since sequence is lagging";
        return;
    }

    if (sequence > m_sequence) {
        emit receivedFrame(m_image);
        qDebug() << "received frame" << m_sequence;
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
    if (lineCount > LINES_SENT) {
        qWarning() << "Invalid line count" << lineCount << "Dropping line";
        return;
    }

    for (auto i = 0; i < lineCount; ++i) {
        memcpy(m_image.scanLine(row + i), offsetPtr, LINE_SIZE);
        offsetPtr += LINE_SIZE;
    }
}
