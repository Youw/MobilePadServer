#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Server;
class CommandExecutor;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:

public slots:
    void start();

private:
    CommandExecutor *executor = nullptr;
    Server *server = nullptr;
};

#endif // CONTROLLER_H
