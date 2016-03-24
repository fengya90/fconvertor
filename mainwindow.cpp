#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar_convert->hide();
    ui->label_per->hide();
    QObject::connect(&thread_, &ConvertThread::ConvertFinished,
                     this, &MainWindow::OnConvertFinished);
    QObject::connect(&thread_, &ConvertThread::ConvertTime,
                     this, &MainWindow::ConvertTime);
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
        QFileInfo fi;
        fi = QFileInfo(filename);
        QString outfile = fi.path()+QDir::separator()+fi.baseName()+"_"+vi.RecommendSize()+"_out.mp4";
        ui->lineEdit_output->setText(outfile);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    thread_.set_input_file(vi.file_path());
    thread_.set_output_file(ui->lineEdit_output->text());
    thread_.set_size(ui->lineEdit_size->text());
    thread_.start();
    setALLEnabled(false);
    ui->progressBar_convert->setValue(0);
    ui->progressBar_convert->show();
    ui->progressBar_convert->setTextVisible(false);
    ui->label_per->setText("0%");
    ui->label_per->show();

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

void MainWindow::setALLEnabled(bool b){
    ui->lineEdit_input->setEnabled(b);
    ui->lineEdit_output->setEnabled(b);
    ui->lineEdit_size->setEnabled(b);
    ui->pushButton->setEnabled(b);
    ui->pushButton_2->setEnabled(b);
    ui->pushButton_input->setEnabled(b);
}

void MainWindow::ConvertTime(int value){
    int v = int(value*100/vi.duration());
    ui->progressBar_convert->setValue(v);
    ui->label_per->setText(QString::number(v)+"%");
}

void MainWindow::OnConvertFinished(){
     ui->progressBar_convert->setValue(100);
     ui->label_per->setText("100%");
     setALLEnabled(true);
     VedioInfo rvi;
     rvi.Parse(ui->lineEdit_output->text());
     ui->textBrowser_output->setText(rvi.ToQStringPurge());
}

