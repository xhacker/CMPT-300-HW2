#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QList>
#include <QMutex>

class Runner// : public QObject
{
//    Q_OBJECT

public:
    Runner();
    void run();
    void check_and_append_input(char);

    int total_operators;
    int total_tools;
    bool paused;
    QList<char> input_buffer;
    QMutex input_mutex;
    QList<char> output_queue;

//signals:
//    void input_changed(QList<char> input_buffer);
};

#endif // RUNNER_H
