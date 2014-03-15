#include "operator.h"
#include <QTime>

Operator::Operator(QObject *parent, Runner *runner, int id) :
    QThread(parent), runner(runner), id(id),
    tools(0), m1(0), m2(0), product(0), take_tool_attemp(0)
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
        QThread::msleep(10);

        while (runner->paused) {
            QThread::msleep(100);
        }

        if (product) {
            runner->output_mutex.lock();
            if (runner->check_and_add_output(product)) {
                runner->add_log(QString("[OP #%1] Put %2 into output queue.").arg(QString::number(id), QString(product)));
                product = 0;
                m1 = m2 = 0;
            }
            runner->output_mutex.unlock();
            continue;
        }

        if (m1 == 0) {
            runner->input_mutex.lock();
            m1 = runner->take_material();
            runner->input_mutex.unlock();
            if (m1) {
                runner->add_log(QString("[OP #%1] Take %2.").arg(QString::number(id), QString(m1)));
            }
            continue;
        }

        if (m2 == 0) {
            char output_top_p = runner->output_queue.first();
            char exclude = 0;
            if (output_top_p == 'X') {
                if (m1 == 'A') {
                    exclude = 'B';
                }
                else if (m1 == 'B') {
                    exclude = 'A';
                }
            }
            else if (output_top_p == 'Y') {
                if (m1 == 'A') {
                    exclude = 'C';
                }
                else if (m1 == 'C') {
                    exclude = 'A';
                }
            }
            else if (output_top_p == 'Z') {
                if (m1 == 'B') {
                    exclude = 'C';
                }
                else if (m1 == 'C') {
                    exclude = 'B';
                }
            }

            runner->input_mutex.lock();
            m2 = runner->take_material_exclude(m1, exclude);
            runner->input_mutex.unlock();
            if (m2) {
                runner->add_log(QString("[OP #%1] Take %2.").arg(QString::number(id), QString(m2)));
            }
            continue;
        }

        if (m1 > m2) {
            char m = m1;
            m1 = m2;
            m2 = m;
        }

        if (tools < 2) {
            if (tools == 1) {
                take_tool_attemp += 1;
            }

            runner->tool_mutex.lock();
            if (runner->take_tool()) {
                tools += 1;
                runner->add_log(QString("[OP #%1] Take tool.").arg(QString::number(id)));
            }
            runner->tool_mutex.unlock();

            if (tools == 2) {
                take_tool_attemp = 0;
            }

            if (take_tool_attemp >= 50) {
                tools -= 1;
                runner->back_tool(1);
                runner->add_log(QString("[OP #%1] Put back tool.").arg(QString::number(id)));
                take_tool_attemp = 0;
            }

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

        while (runner->paused) {
            QThread::msleep(100);
        }

        product = p;
        tools = 0;
        runner->back_tool(2);
    }
}
