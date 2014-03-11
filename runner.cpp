#include "runner.h"
#include "generator.h"
#include "operator.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Runner::Runner() : paused(false)
{   
}

void Runner::check_and_append_input(char m)
{
    if (input_buffer.size() < 10) {
        input_buffer.append(m);
        emit input_changed(input_buffer);
    }
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
