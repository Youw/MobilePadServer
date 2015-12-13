#include "controller.h"

#include <QDebug>

#include "commandexecutor.h"
#include "server.h"

Controller::Controller(QObject *parent)
    : QObject(parent)
{

}

void Controller::start()
{
    if (!server)
    {
        executor = new CommandExecutor(this);
        server = new Server(this);
        connect(server, &Server::commandArrived, executor, &CommandExecutor::executeCommand);
    }
    qDebug() << "Controller started";
    server->start();
}

