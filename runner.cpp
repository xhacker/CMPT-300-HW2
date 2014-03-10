#include "runner.h"
#include "generator.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Runner::Runner() : paused(false)
{
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

    while (true) {
        sleep(1);
        for (int i = 0; i < input_buffer.size(); ++i) {
            cout << input_buffer[i];
        }
        cout << endl;
    }
}
