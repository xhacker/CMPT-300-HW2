#ifndef RUNNER_H
#define RUNNER_H

#include <QList>
#include <QMutex>

class Runner
{
public:
    Runner();
    void run();

    int total_operators;
    int total_tools;
    bool paused;
    QList<char> input_buffer;
    QMutex input_mutex;
    QList<char> output_queue;

private:
};

#endif // RUNNER_H
