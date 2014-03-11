#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QList>
#include <QMutex>

class Runner : public QObject
{
    Q_OBJECT

public:
    Runner();
    void run();
    void check_and_add_input(char);
    bool check_and_add_output(char);
    char take_material();

    int total_operators;
    int total_tools;
    bool paused;
    QList<char> input_buffer;
    QMutex input_mutex;
    QList<char> output_queue;
    QMutex output_mutex;

signals:
    void input_changed(QList<char> input_buffer);
    void output_changed(QList<char> output_queue);
};

#endif // RUNNER_H
