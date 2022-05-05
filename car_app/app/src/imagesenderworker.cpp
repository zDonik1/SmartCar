/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/05/2022
 *
 *************************************************************************/

#include <imagesenderworker.h>

#include <QDebug>
#include <QThread>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <common.h>

using namespace cv;

// a bit of pause between datagrams to prevent network overloading in car
constexpr auto DATAGRAM_TX_RATE = 1; // ms, 1000 / (DATAGRAMS_PER_FRAME * FPS)

ImageSenderWorker::ImageSenderWorker(const QHostAddress &host, QObject *parent)
    : QObject(parent), m_host(host)
{
    connect(this, &ImageSenderWorker::sendFrame, this, &ImageSenderWorker::onSendFrame);

    connect(
        &m_socket,
        &QAbstractSocket::stateChanged,
        this,
        [this](auto state) { qDebug() << "Socket state changed:" << state; },
        Qt::DirectConnection);
}

void ImageSenderWorker::start()
{
    if (m_running)
        return;

    lock_guard<mutex> socketLock(m_mutex);
    m_socket.connectToHost(m_host, FRAME_PORT);
    m_running = true;
}

void ImageSenderWorker::stop()
{
    if (!m_running)
        return;

    lock_guard<mutex> socketLock(m_mutex);
    m_socket.disconnectFromHost();
    m_running = false;
}

void ImageSenderWorker::onSendFrame(FramePtr frame)
{
    lock_guard<mutex> lock(m_mutex);
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

            if (m_socket.write(buffer.data(), buffer.size()) < 0) {
                qWarning() << "Failed to send datagram:" << m_socket.errorString();
            }
            lineCount = 0;
            offsetPtr = buffer.data();
            QThread::msleep(DATAGRAM_TX_RATE);
        }
    }
}
