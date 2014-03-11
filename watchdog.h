#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QThread>
#include "runner.h"

class Watchdog : public QThread
{
    Q_OBJECT

public:
    Watchdog(QObject *parent = 0, Runner *runner = 0);

signals:

public slots:

private:
    void run();

    Runner *runner;
};

#endif // WATCHDOG_H
