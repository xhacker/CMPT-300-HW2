#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "runner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_runButton_clicked();
    void on_pauseButton_clicked();

public slots:
    void update_input(QList<char>);

private:
    Ui::MainWindow *ui;
    Runner runner;
};

#endif // MAINWINDOW_H
