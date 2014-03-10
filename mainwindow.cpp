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

void MainWindow::update_input(QList<char> buffer)
{
    for (int i = 0; i < buffer.size(); ++i) {
        cout << buffer[i];
    }
    cout << endl;
}

void MainWindow::on_runButton_clicked()
{
    ui->pauseButton->setEnabled(true);

    qRegisterMetaType<QList<char> >("QList<char>");
    QObject::connect(&runner, SIGNAL(input_changed(QList<char>)),
                     this, SLOT(update_input(QList<char>)));

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
