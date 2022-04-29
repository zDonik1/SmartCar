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

constexpr auto IPV4 = "192.168.100.180";

ImageSender::ImageSender(shared_ptr<ImageProcessor> imageProcessor, QObject *parent)
    : QObject{parent}, m_imageProcessor(imageProcessor)
{
    connect(&m_socket, &QTcpSocket::stateChanged, this, [this, imageProcessor](auto state) {
        qDebug() << "Socket state changed:" << state;

        if (m_socket.state() == QTcpSocket::ConnectedState) {
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

    connect(&m_socket, &QTcpSocket::errorOccurred, this, [this] { qDebug() << m_socket.error(); });

    m_socket.connectToHost(IPV4, PORT);
}

void ImageSender::sendFrame(FramePtr frame)
{
    if (frame->image.type() != CV_8UC3) {
        qWarning() << "Unknown format of image";
        return;
    }

    Mat mat(SCALED_IMAGE_HEIGHT, SCALED_IMAGE_WIDTH, CV_8UC3);
    resize(frame->image, mat, mat.size(), 0, 0, INTER_AREA);
    for (int i = 0; i < mat.rows; ++i) {
        auto bytes = m_socket.write(reinterpret_cast<const char *>(mat.row(i).data),
                                    mat.cols * PIXEL_SIZE);
        if (bytes < 0) {
            qWarning() << "Couldn't send frame";
            return;
        }
    }
    qDebug() << "sent frame" << frame->sequence;
}
