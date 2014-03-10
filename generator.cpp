#include "generator.h"
#include <cstdio>

Generator::Generator(QObject *parent, Runner *runner, char material) :
    QThread(parent), runner(runner), material(material)
{
}

int Generator::rand_int(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

void Generator::run()
{
    while (true) {
        QThread::msleep(rand_int(10, 1000));

        runner->input_mutex.lock();
        runner->check_and_append_input(material);
        runner->input_mutex.unlock();
    }
}
