#include "commandexecutor.h"

#include <QDebug>

CommandExecutor::CommandExecutor(QObject *parent) : QObject(parent)
{

}

void CommandExecutor::executeCommand(const QString &command)
{
    qDebug() << "Command:" << command;
}

