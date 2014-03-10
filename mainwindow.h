#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    int total_operators;
    int total_tools;
    bool paused;
};

#endif // MAINWINDOW_H
