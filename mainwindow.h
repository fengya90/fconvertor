#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vedioinfo.h"
#include "convertthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setALLEnabled(bool b);

private slots:
    void on_pushButton_input_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void ConvertTime(int newValue);
    void OnConvertFinished();

private:
    Ui::MainWindow *ui;
    VedioInfo vi;
    ConvertThread thread_;
};

#endif // MAINWINDOW_H
