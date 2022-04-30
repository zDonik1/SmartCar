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

ImageSender::ImageSender(shared_ptr<ImageProcessor> imageProcessor,
                         QHostAddress address,
                         QObject *parent)
    : QObject(parent), m_address(address), m_imageProcessor(imageProcessor)
{
    connect(&m_socket, &QAbstractSocket::stateChanged, this, [this, imageProcessor](auto state) {
        qDebug() << "Socket state changed:" << state;

        if (m_socket.state() == QAbstractSocket::ConnectedState) {
            connect(imageProcessor.get(),
                    &ImageProcessor::frameReady,
                    this,
                    &ImageSender::sendFrame);
        } else {
            disconnect(imageProcessor.get(),
                       &ImageProcessor::frameReady,
                       this,
                       &ImageSender::sendFrame);
        }
    });

    connect(&m_socket, &QAbstractSocket::errorOccurred, this, [this] { qDebug() << m_socket.error(); });

    m_socket.connectToHost(m_address, PORT);
}

void ImageSender::sendFrame(FramePtr frame)
{
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
    qDebug() << "sent frame" << frame->sequence;
}
