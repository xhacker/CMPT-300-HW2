#include "runner.h"
#include "generator.h"
#include "operator.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Runner::Runner() : paused(false)
{   
}

void Runner::check_and_add_input(char m)
{
    if (input_buffer.size() < 10) {
        input_buffer.prepend(m);
        emit input_changed(input_buffer);
    }
}

bool Runner::check_and_add_output(char p)
{
    if (output_queue.size() == 0 || output_queue.first() != p) {
        output_queue.prepend(p);
        emit output_changed(output_queue);
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
    char m = input_buffer.takeLast();
    emit input_changed(input_buffer);
    return m;
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
}
