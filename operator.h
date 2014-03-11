#ifndef OPERATOR_H
#define OPERATOR_H

#include <QThread>
#include "runner.h"

class Operator : public QThread
{
    Q_OBJECT

public:
    Operator(QObject *parent, Runner *runner, int id);

signals:

public slots:

private:
    void run();
    int rand_int(int, int);

    Runner *runner;
    int id;
    int tools = 0;
    char m1 = 0, m2 = 0;
    char product = 0;
};

#endif // OPERATOR_H
