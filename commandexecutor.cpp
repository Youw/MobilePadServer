#include "commandexecutor.h"

#include <QDebug>
#include <QHash>

namespace {

enum class Command {
    KEY_DOWN,
    KEY_UP,
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_MOVE,
    MOUSE_WHEEL
};

} // anonymous

QHash<QString, Command> command_enum {
    {QString("KEY_UP"     ), Command::KEY_UP     },
    {QString("KEY_DOWN"   ), Command::KEY_DOWN   },
    {QString("MOUSE_UP"   ), Command::MOUSE_UP   },
    {QString("MOUSE_DOWN" ), Command::MOUSE_DOWN },
    {QString("MOUSE_MOVE" ), Command::MOUSE_MOVE },
    {QString("MOUSE_WHEEL"), Command::MOUSE_WHEEL},
};

CommandExecutor::CommandExecutor(QObject *parent) : QObject(parent)
{

}

void CommandExecutor::executeCommand(const QString &command_str)
{
    QStringList command = command_str.split(':', QString::KeepEmptyParts);
    if (command_enum.contains(command[0]))
    {
        qDebug() << "Command:" << command_str;
        switch (command_enum[command[0]]) {
        case Command::KEY_DOWN:
            execKey(KEY_DOWN, command[1]);
            break;
        case Command::KEY_UP:
            execKey(KEY_UP, command[1]);
            break;
        case Command::MOUSE_DOWN:
            execMouseKey(BUTTON_PRESS, command[1]);
            break;
        case Command::MOUSE_UP:
            execMouseKey(BUTTON_RELEASE, command[1]);
            break;
        case Command::MOUSE_MOVE:
            mouseMove(command[1].toInt(), command[2].toInt());
            break;
        case Command::MOUSE_WHEEL:
            mouseWheel(command[1].toInt());
            break;
        }
    }
    else
    {
        qDebug() << "Unrecognized command:" << command_str;
    }
}

