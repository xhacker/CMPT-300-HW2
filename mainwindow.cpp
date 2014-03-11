#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
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
    input_model = new QStringListModel(0);
    QStringList List;

    int count[3] = {0};

    for (int i = 0; i < buffer.size(); ++i) {
        List.append(QString(buffer[i]));
        count[buffer[i] - 'A'] += 1;
    }

    input_model->setStringList(List);
    ui->inputListView->setModel(input_model);

    ui->materialsBrowser->setText(QString("A: %1\nB: %2\nC: %3\nTools: %4\n")
                                  .arg(QString::number(count[0]),
                                       QString::number(count[1]),
                                       QString::number(count[2]),
                                       QString::number(runner.total_tools)));
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
