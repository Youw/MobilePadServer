#include "server.h"

#include <QDebug>
#include <QNetworkInterface>
#include <QTcpSocket>

Server::Server(QObject *parent)
    : QObject(parent)
{
    connect(&socket, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

void Server::start()
{
    if (!socket.isListening())
    {
        socket.listen(QHostAddress::Any, 8887);
        if (socket.isListening())
        {
            qDebug() << "Server started at" << QString("%1:%2").arg(socket.serverAddress().toString()).arg(socket.serverPort());
            qDebug() << "Local IPs:";
            foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
                if (address != QHostAddress(QHostAddress::LocalHost) && !address.isLoopback())
                {
                    qDebug() << address.toString();
                }
            }
        }
        else
        {
            qDebug() << "SOcket start failed:" << socket.errorString();
        }
    }
}

void Server::onNewConnection()
{
    while(socket.hasPendingConnections())
    {
        QTcpSocket *client = socket.nextPendingConnection();
        client_description[client] = QString("%1:%2").arg(client->peerAddress().toString()).arg(client->peerPort());
        connect(client, &QTcpSocket::readyRead, this, &Server::onDataCome);
        connect(client, &QTcpSocket::disconnected, this,&Server::onClientDisconnected);
    }
}

void Server::onDataCome()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    while(client->canReadLine())
    {
        QString line = client->readLine().trimmed();
        emit commandArrived(line);
    }
}

void Server::onClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    qDebug() << "Client disconnected:" << client_description[client];
    client_description.remove(client);
    client->deleteLater();
}

