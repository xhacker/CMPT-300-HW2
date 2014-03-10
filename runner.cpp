#include "runner.h"
#include <iostream>

using namespace std;

Runner::Runner() : paused(false)
{
}

void Runner::run()
{
    cout << "Running: " << total_operators << " operators, " << total_tools << " tools." << endl;
}
