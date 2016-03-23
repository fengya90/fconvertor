#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vedioinfo.h"

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
    void on_pushButton_input_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    VedioInfo vi;
};

#endif // MAINWINDOW_H
