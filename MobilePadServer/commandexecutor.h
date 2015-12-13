#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H

#include <QObject>

class CommandExecutor : public QObject
{
    Q_OBJECT
public:
    explicit CommandExecutor(QObject *parent = 0);

public slots:
    void executeCommand(const QString &command);
};

#endif // COMMANDEXECUTOR_H
