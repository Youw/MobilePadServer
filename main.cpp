#include <QCoreApplication>

#include <QMetaObject>

#include "controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Controller c;

    QMetaObject::invokeMethod(&c, "start", Qt::QueuedConnection);

    return a.exec();
}

