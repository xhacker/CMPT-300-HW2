#include "watchdog.h"
#include <QTime>
#include <cstdio>

Watchdog::Watchdog(QObject *parent, Runner *runner) :
    QThread(parent), runner(runner)
{
}

void Watchdog::run()
{
    while (true) {
        QThread::msleep(100);

        if (runner->timer.elapsed() - runner->last_activity_time > 1500) {
            runner->add_log("[Warning] Dead lock detected.");
            printf("Dead lock: %d, %d.\n", runner->timer.elapsed(), runner->last_activity_time);
            break;
        }
    }
}
