#include "generator.h"
#include <QTime>

Generator::Generator(QObject *parent, Runner *runner, char material) :
    QThread(parent), runner(runner), material(material)
{
    QTime time = QTime::currentTime();
    srand((uint)time.msec() + material);
}

int Generator::rand_int(int low, int high)
{
    return rand() % ((high + 1) - low) + low;
}

void Generator::run()
{
    while (true) {
        QThread::msleep(rand_int(10, 1000));

        while (runner->paused) {
            QThread::msleep(100);
        }

        runner->input_mutex.lock();
        runner->check_and_add_input(material);
        runner->input_mutex.unlock();
    }
}
