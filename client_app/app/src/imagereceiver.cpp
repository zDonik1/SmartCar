/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 26/04/2022
 *
 *************************************************************************/

#include <imagereceiver.h>

#include <QHostAddress>
#include <QTimer>

#include <common.h>

using namespace std;
using namespace cv;

ImageReceiver::ImageReceiver(QObject *parent)
    : QObject{parent}
{
    connect(&m_server, &QTcpServer::newConnection, this, [this] {
        m_socket = m_server.nextPendingConnection();
        qDebug() << "Connection established on" << m_socket->peerAddress() << "with port"
                 << m_socket->peerPort();

        connect(m_socket, &QTcpSocket::stateChanged, this, [this](auto state) {
            qDebug() << "Socket state changed:" << state;

            if (m_socket->state() == QTcpSocket::UnconnectedState) {
                listenToConnections();
            }
        });

        connect(m_socket, &QTcpSocket::readyRead, this, &ImageReceiver::readFrames);
    });
}

void ImageReceiver::start()
{
    listenToConnections();
}

void ImageReceiver::readFrames()
{
    if (m_socket->bytesAvailable() < IMAGE_SIZE)
        return;

    Mat image(CAPTURE_HEIGHT, CAPTURE_WIDTH, CV_8UC3);
    m_socket->read(reinterpret_cast<char *>(image.data), IMAGE_SIZE);
    emit receivedFrame({m_sequence++, image});
}

void ImageReceiver::listenToConnections()
{
    m_server.listen(QHostAddress::Any, PORT);
    qDebug() << "Started listening to connections on port" << PORT;
}
