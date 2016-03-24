#ifndef CONVERTTHREAD_H
#define CONVERTTHREAD_H

#include <QThread>
#include <QString>

class ConvertThread: public  QThread
{
    Q_OBJECT
public:
    ConvertThread();
    void set_input_file(const QString& v){input_file_ = v;}
    void set_output_file(const QString& v){output_file_ = v;}
    void set_size(const QString& v){size_ = v;}
signals:
    void ConvertTime(int newValue);
    void ConvertFinished();
protected:
       void run();
private:
        QString input_file_;
        QString output_file_;
        QString size_;
};

#endif // CONVERTTHREAD_H
