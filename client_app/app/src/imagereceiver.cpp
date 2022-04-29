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

        m_timer.start();
    });
}

void ImageReceiver::start()
{
    listenToConnections();
}

void ImageReceiver::readFrames()
{
    constexpr static auto BYTES_PER_LINE = SCALED_IMAGE_WIDTH * PIXEL_SIZE;

    if (m_socket->bytesAvailable() < BYTES_PER_LINE)
        return;

    m_socket->read(reinterpret_cast<char *>(m_image.scanLine(m_row++)), BYTES_PER_LINE);
    qDebug() << (m_bytesRead += BYTES_PER_LINE) / m_timer.elapsed() << "bytes per ms";

    if (m_row >= SCALED_IMAGE_HEIGHT) {
        m_row = 0;
        emit receivedFrame(m_image);
    }
}

void ImageReceiver::listenToConnections()
{
    m_server.listen(QHostAddress::Any, PORT);
    qDebug() << "Started listening to connections on port" << PORT;
}
