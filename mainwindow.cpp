#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    paused = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_runButton_clicked()
{
    total_operators = ui->operatorsSpinBox->value();
    total_tools = ui->toolsSpinBox->value();

    ui->pauseButton->setEnabled(true);

    cout << "Running: " << total_operators << " operators, " << total_tools << " tools." << endl;
}

void MainWindow::on_pauseButton_clicked()
{
    paused = !paused;
    if (paused) {
        ui->pauseButton->setText("Resume");
    }
    else {
        ui->pauseButton->setText("Pause");
    }
}
