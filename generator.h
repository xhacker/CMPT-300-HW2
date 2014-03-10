#ifndef GENERATOR_H
#define GENERATOR_H

#include <QThread>
#include "runner.h"

class Generator : public QThread
{
    Q_OBJECT

public:
    Generator(QObject *parent = 0, Runner *runner = 0, char material = 'A');

signals:

public slots:

private:
    void run();
    int rand_int(int, int);

    Runner *runner;
    char material;
};

#endif // GENERATOR_H
