#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{
    ui->pauseButton->setEnabled(true);

    runner.total_operators = ui->operatorsSpinBox->value();
    runner.total_tools = ui->toolsSpinBox->value();
    runner.run();
}

void MainWindow::on_pauseButton_clicked()
{
    runner.paused = !runner.paused;
    if (runner.paused) {
        ui->pauseButton->setText("Resume");
    }
    else {
        ui->pauseButton->setText("Pause");
    }
}
