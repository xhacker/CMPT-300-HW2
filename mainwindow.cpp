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

    input_model = new QStringListModel(0);
    output_model = new QStringListModel(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_input(QList<char> buffer)
{
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
                                       QString::number(runner.remain_tools)));
}

void MainWindow::update_output(QList<char> queue)
{
    QStringList List;

    int count[3] = {0};

    for (int i = 0; i < queue.size(); ++i) {
        List.append(QString(queue[i]));
        count[queue[i] - 'X'] += 1;
    }

    output_model->setStringList(List);
    ui->outputListView->setModel(output_model);

    ui->productsBrowser->setText(QString("X: %1\nY: %2\nZ: %3\n")
                                  .arg(QString::number(count[0]),
                                       QString::number(count[1]),
                                       QString::number(count[2])));
}

void MainWindow::update_log(QString log)
{
    ui->logBrowser->setText(log + "\n" + ui->logBrowser->toPlainText());
}

void MainWindow::on_runButton_clicked()
{
    ui->pauseButton->setEnabled(true);
    ui->runButton->setEnabled(false);

    qRegisterMetaType<QList<char> >("QList<char>");
    QObject::connect(&runner, SIGNAL(input_changed(QList<char>)),
                     this, SLOT(update_input(QList<char>)));
    QObject::connect(&runner, SIGNAL(output_changed(QList<char>)),
                     this, SLOT(update_output(QList<char>)));
    QObject::connect(&runner, SIGNAL(log_added(QString)),
                     this, SLOT(update_log(QString)));

    runner.total_operators = ui->operatorsSpinBox->value();
    runner.total_tools = ui->toolsSpinBox->value();
    runner.remain_tools = runner.total_tools;
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
