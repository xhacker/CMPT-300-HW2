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
    int tools;
    char m1, m2;
    char product;
    int take_tool_attemp;
};

#endif // OPERATOR_H
