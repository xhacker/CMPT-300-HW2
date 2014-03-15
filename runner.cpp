#include "runner.h"
#include "generator.h"
#include "operator.h"
#include "watchdog.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Runner::Runner() : paused(false)
{
    timer.start();
    refresh_activity_time();
}

void Runner::refresh_activity_time()
{
    last_activity_time = timer.elapsed();
}

void Runner::check_and_add_input(char m)
{
    if (input_buffer.size() < 10) {
        input_buffer.prepend(m);
        emit input_changed(input_buffer);
        refresh_activity_time();
    }
}

bool Runner::check_and_add_output(char p)
{
    int count_X = output_queue.count('X');
    int count_Y = output_queue.count('Y');
    int count_Z = output_queue.count('Z');
    int count_min = min(min(count_X, count_Y), count_Z);
    int count_p = output_queue.count(p);

    if (output_queue.size() == 0 || (output_queue.first() != p && count_p + 1 - count_min < 10)) {
        output_queue.prepend(p);
        emit output_changed(output_queue);
        refresh_activity_time();
        return true;
    }
    return false;
}

void Runner::add_log(QString log)
{
    emit log_added(log);
}

char Runner::take_material()
{
    if (input_buffer.size() == 0) {
        return 0;
    }

    char m = input_buffer.takeLast();
    emit input_changed(input_buffer);
    refresh_activity_time();
    return m;
}

char Runner::take_material_exclude(char e1, char e2)
{
    if (input_buffer.size() == 0) {
        return 0;
    }

    for (int i = input_buffer.size() - 1; i >= 0; --i) {
        char m = input_buffer[i];
        if (m != e1 && m != e2) {
            input_buffer.removeAt(i);
            emit input_changed(input_buffer);
            refresh_activity_time();
            return m;
        }
    }

    return 0;
}

bool Runner::take_tool()
{
    if (remain_tools > 0) {
        remain_tools -= 1;
        emit input_changed(input_buffer);
        refresh_activity_time();
        return true;
    }
    return false;
}

void Runner::back_tool(int amount)
{
    remain_tools += amount;
    emit input_changed(input_buffer);
    refresh_activity_time();
}

void Runner::run()
{
    cout << "Running: " << total_operators << " operators, " << total_tools << " tools." << endl;

    Generator *g1 = new Generator(0, this, 'A');
    Generator *g2 = new Generator(0, this, 'B');
    Generator *g3 = new Generator(0, this, 'C');

    g1->start();
    g2->start();
    g3->start();

    for (int i = 1; i <= total_operators; ++i) {
        Operator *op = new Operator(0, this, i);
        op->start();
    }

    Watchdog *dog = new Watchdog(0, this);
    dog->start();
}
