/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imagesender.h>

#include <QHostAddress>
#include <QTimer>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <common.h>

using namespace std;
using namespace cv;

ImageSender::ImageSender(QHostAddress address,
                         QObject *parent)
    : IImageSender(parent), m_address(address)
{
    connect(&m_socket, &QAbstractSocket::stateChanged, this, [this](auto state) {
        qDebug() << "Socket state changed:" << state;
    });

    connect(&m_socket, &QAbstractSocket::errorOccurred, this, [this] {
        qDebug() << m_socket.error();
    });
}

ImageSender::~ImageSender()
{
    ImageSender::stop();
}

void ImageSender::start()
{
    if (m_running)
        return;

    m_socket.connectToHost(m_address, PORT);
    m_running = true;
}

void ImageSender::stop()
{
    if (!m_running)
        return;

    m_socket.disconnectFromHost();
    m_running = false;
}

void ImageSender::sendFrame(FramePtr frame)
{
    if (!m_running || m_socket.state() != QAbstractSocket::ConnectedState)
        return;

    if (frame->image.type() != CV_8UC3) {
        qWarning() << "Unknown format of image";
        return;
    }

    Mat mat(SCALED_IMAGE_HEIGHT, SCALED_IMAGE_WIDTH, CV_8UC3);
    resize(frame->image, mat, mat.size(), 0, 0, INTER_NEAREST);

    array<char, DATAGRAM_SIZE> buffer;
    auto lineCount = 0;
    auto offsetPtr = buffer.data();
    for (RowType i = 0; i < mat.rows; ++i) {
        if (lineCount == 0) {
            memcpy(offsetPtr, reinterpret_cast<char *>(&frame->sequence), SEQUENCE_SIZE);
            offsetPtr += SEQUENCE_SIZE;
            memcpy(offsetPtr, reinterpret_cast<char *>(&i), ROW_SIZE);
            offsetPtr += ROW_SIZE + LINE_COUNT_SIZE;
        }

        memcpy(offsetPtr, mat.row(i).data, LINE_SIZE);
        offsetPtr += LINE_SIZE;
        ++lineCount;

        if (lineCount == LINES_SENT || i == mat.rows - 1) {
            memcpy(buffer.data() + SEQUENCE_SIZE + ROW_SIZE,
                   reinterpret_cast<char *>(&lineCount),
                   ROW_SIZE);
            while (m_socket.write(buffer.data(), buffer.size()) < 0) {
                qWarning() << "Retrying sending line due to" << m_socket.error();
            }
            lineCount = 0;
            offsetPtr = buffer.data();
        }
    }
    qDebug() << "Sent frame" << frame->sequence << ", fps:" << frame->framerate;
}
