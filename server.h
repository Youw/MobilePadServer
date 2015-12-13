#ifndef SERVER_H
#define SERVER_H

#include <QHash>
#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:
    void commandArrived(const QString &command);

public slots:
    void start();

private slots:
    void onNewConnection();
    void onDataCome();
    void onClientDisconnected();

private:
    QTcpServer socket;
    QHash<QTcpSocket*, QString> clients_description;
};

#endif // SERVER_H
