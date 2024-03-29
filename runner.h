#ifndef RUNNER_H
#define RUNNER_H

#include <QObject>
#include <QList>
#include <QMutex>
#include <QTime>

class Runner : public QObject
{
    Q_OBJECT

public:
    Runner();
    void run();
    void check_and_add_input(char);
    bool check_and_add_output(char);
    void add_log(QString);
    char take_material();
    char take_material_exclude(char, char);
    bool take_tool();
    void back_tool(int);

    bool paused;
    QTime timer;
    int total_operators;
    int total_tools;
    int remain_tools;
    int last_activity_time;
    QMutex tool_mutex;
    QList<char> input_buffer;
    QMutex input_mutex;
    QList<char> output_queue;
    QMutex output_mutex;

signals:
    void input_changed(QList<char> input_buffer);
    void output_changed(QList<char> output_queue);
    void log_added(QString log);

private:
    void refresh_activity_time();
};

#endif // RUNNER_H
