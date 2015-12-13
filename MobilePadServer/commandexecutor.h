#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <QObject>

class CommandExecutor : public QObject
{
    Q_OBJECT
public:
    explicit CommandExecutor(QObject *parent = 0);

    enum KeyCommandType {
        KEY_DOWN,
        KEY_UP,
    };

    enum MouseKeyCommandType {
        BUTTON_PRESS,
        BUTTON_RELEASE,
    };

public slots:
    void executeCommand(const QString &command);

protected:
    void execKey(KeyCommandType type, const QString &key);
    void execMouseKey(MouseKeyCommandType type, const QString &button);
    void mouseMove(int dx, int dy);
    void mouseWheel(int dx);

    float mouse_move_speed = 1.;
    float mouse_wheel_speed = 1.;
};

#endif // COMMANDEXECUTOR_H
