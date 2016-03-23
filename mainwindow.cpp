#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vedioinfo.h"
#include <QFileDialog>
#include <QDir>

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
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
                                            tr("choose video"),
                                            "",
                                            tr("Video (*.mp4 *.flv *.avi *.mov *.rmvb)")); //选择路径
    if(filename.isEmpty())
    {
        return;
    }else{
        vi.Parse(filename);
        ui->lineEdit_input->setText(filename);
        ui->textBrowser_input->setText(vi.ToQString());
        ui->lineEdit_size->setText(vi.RecommendSize());
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    QString filename;
    filename = QFileDialog::getExistingDirectory();
    if(filename.isEmpty())
    {
        return;
    }
    else
    {
        QString  orifile = ui->lineEdit_input->text();
        QFileInfo fi;
        fi = QFileInfo(orifile);
        QString outfile = filename+QDir::separator()+fi.baseName()+"_"+vi.RecommendSize()+"_out.mp4";
        ui->lineEdit_output->setText(outfile);
    }
}

