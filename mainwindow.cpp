#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar_convert->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_input_clicked()
{
    ui->progressBar_convert->show();
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{

}
