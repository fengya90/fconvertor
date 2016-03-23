#include "convertthread.h"
#include <QProcess>
#include "util.h"

ConvertThread::ConvertThread()
{

}

void ConvertThread::run()
{
    QProcess process;
    QStringList argv;
    argv<<"-i"<<input_file_<<"-s"<<size_<<output_file_;
    process.start(Util::program_ffmpeg(),argv);
    if (!process.waitForStarted())
    {
        qDebug( "start error!");
        return;
    }
    while(!process.waitForFinished(5000)){
        QByteArray procOutput;
        procOutput = process.readAllStandardError();
        QString ret = QString::fromLocal8Bit(procOutput.data(),procOutput.size());
        qDebug(ret.toStdString().c_str());
    }
    qDebug( "finish!");
    ConvertFinished(0);

}

