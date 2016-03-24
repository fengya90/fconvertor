#include "convertthread.h"
#include <QProcess>
#include <QFile>
#include "util.h"

ConvertThread::ConvertThread()
{

}

void ConvertThread::run()
{
    QString pattern("\\d\\d:\\d\\d:\\d\\d");
    QRegExp rx(pattern);
    QFile::remove(output_file_);
    QProcess process;
    QStringList argv;
    argv<<"-i"<<input_file_<<"-s"<<size_<<output_file_;
    process.start(Util::program_ffmpeg(),argv);
    if (!process.waitForStarted())
    {        
        return;
    }
    while(!process.waitForFinished(5000)){
        QByteArray procOutput;
        procOutput = process.readAllStandardError();
        QString ret = QString::fromLocal8Bit(procOutput.data(),procOutput.size()).split("\n").last();        
        int pos = ret.indexOf(rx);
        if(pos<0){
            continue;
        }
        QString tstr = rx.capturedTexts().at(0);
        QStringList seclist = tstr.split(":");
        if(seclist.size()==3){
            int retv = seclist.at(0).toInt()*3600+seclist.at(1).toInt()*60+seclist.at(2).toInt();
            ConvertTime(retv);
        }
    }    
    ConvertFinished();

}

