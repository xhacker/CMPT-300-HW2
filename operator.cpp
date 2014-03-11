#include "operator.h"
#include <QTime>

Operator::Operator(QObject *parent, Runner *runner, int id) :
    QThread(parent), runner(runner), id(id)
{
    QTime time = QTime::currentTime();
    srand((uint)time.msec() + id);
}

int Operator::rand_int(int low, int high)
{
    return rand() % ((high + 1) - low) + low;
}

void Operator::run()
{
    while (true) {
        QThread::msleep(rand_int(10, 1000));

        char m1 = 0, m2 = 0;

        runner->input_mutex.lock();
        if (runner->input_buffer.size() >= 2) {
            m1 = runner->input_buffer.takeFirst();
            m2 = runner->input_buffer.takeFirst();
        }
        runner->input_mutex.unlock();
    }
}
