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

        if (product) {
            runner->output_mutex.lock();
            if (runner->check_and_add_output(product)) {
                product = 0;
                m1 = m2 = 0;
                tools = 0;
                runner->back_tool(2);
            }
            runner->output_mutex.unlock();
            continue;
        }

        if (m1 == 0) {
            runner->input_mutex.lock();
            m1 = runner->take_material();
            runner->input_mutex.unlock();
            continue;
        }

        if (m2 == 0) {
            runner->input_mutex.lock();
            m2 = runner->take_material();
            runner->input_mutex.unlock();
            continue;
        }

#warning m2 shouldn't be equal to m1

        if (m1 > m2) {
            char m = m1;
            m1 = m2;
            m2 = m;
        }

        if (tools < 2) {
            runner->tool_mutex.lock();
            if (runner->take_tool()) {
                tools += 1;
            }
            runner->tool_mutex.unlock();
            continue;
        }

        char p;
        if (m1 == 'A' && m2 == 'B') {
            p = 'X';
        }
        else if (m1 == 'A' && m2 == 'C') {
            p = 'Y';
        }
        else {
            // m1 == 'B' && m2 == 'C'
            p = 'Z';
        }

        runner->add_log(QString("[OP #%1] Producing %2.").arg(QString::number(id), QString(p)));

        QThread::msleep(rand_int(10, 1000));

        product = p;
    }
}
