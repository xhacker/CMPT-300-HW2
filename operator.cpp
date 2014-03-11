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
        QThread::msleep(50);

        char m1 = 0, m2 = 0;

        runner->input_mutex.lock();
        if (runner->input_buffer.size() >= 2) {
            m1 = runner->take_material();
            m2 = runner->take_material();
        }
        runner->input_mutex.unlock();

        if (m1 > m2) {
            char m = m1;
            m1 = m2;
            m2 = m;
        }

        QThread::msleep(rand_int(10, 1000));

        char product;
        if (m1 == 'A' && m2 == 'B') {
            product = 'X';
        }
        else if (m1 == 'A' && m2 == 'C') {
            product = 'Y';
        }
        else {
            // m1 == 'B' && m2 == 'C'
            product = 'Z';
        }

        runner->output_mutex.lock();
        runner->check_and_add_output(product);
#warning if not added, add next time
        runner->output_mutex.unlock();
    }
}
