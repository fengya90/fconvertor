#include "vedioinfo.h"
#include <QProcess>
#include "util.h"

VedioInfo::VedioInfo()
{
    parse_ok_ = false;
}

bool VedioInfo::Parse(QString file_path){
    file_path_ = file_path;
    QProcess process;
    QString argv = "-show_format -v error -of flat=s=_ -select_streams v:0 -show_entries stream=height,width";
    QStringList argvlist = argv.split(" ");
    argvlist<<file_path;
    process.start(Util::program_ffprobe(),argvlist);
    if (!process.waitForStarted())
    {
        parse_ok_ = false;
        return false;
    }

    if(!process.waitForFinished()){
        parse_ok_ = false;
        return false;
    }
    QByteArray procOutput;
    procOutput = process.readAll();
    QString ret = QString::fromLocal8Bit(procOutput.data(),procOutput.size());
    QStringList tmplist = ret.split("\n");
    for (QStringList::iterator it = tmplist.begin();it != tmplist.end(); ++it) {
           QString current = *it;
           QStringList kv = current.split("=");
           if(kv.size() != 2){
               continue;
           }
           if(kv.at(0) == "streams_stream_0_width"){
               width_ = kv.at(1).toUInt();
           }else if(kv.at(0) == "streams_stream_0_height"){
                height_ = kv.at(1).toUInt();
           }else if(kv.at(0) == "format_duration"){
               QStringList tmplist2 = kv.at(1).split("\"");
               if(tmplist2.size() == 3){
                    duration_ = tmplist2.at(1).toDouble();
               }
           }else if(kv.at(0) == "format_size"){
               QStringList tmplist2 = kv.at(1).split("\"");
               if(tmplist2.size() == 3){
                    size_ = tmplist2.at(1).toULongLong();
               }
           }
    }
    return true;
}

QString VedioInfo::ToQString(){
    QString content;
    content.append("文件路径:\t"+file_path_+"\n");
    content.append("宽x高:\t");
    content.append(QString::number(width_));
    content.append('x');
    content.append(QString::number(height_));
    content.append("\n");
    content.append("时长:\t");
    uint32_t duration = static_cast<uint64_t> (duration_);
    uint32_t min = duration/60;
    uint32_t sec = duration%60;
    content.append(QString::number(min));
    content.append(":");
    content.append(QString::number(sec));
    content.append("\n");
    content.append("大小:\t");
    content.append(QString::number(size_));
    content.append("Bytes(");
    content.append(Util::GetHumanReadable(size_));
    content.append(")");
    content.append("\n");
    content.append("建议缩放大小:");
    if(RecommendSize().size() == 0){
        content.append("无建议");
    }else{
        content.append(RecommendSize());
    }
    content.append("  (建议长宽等比例缩放为原视频的1/2或者1/3)");
    return content;
}

QString VedioInfo::ToQStringPurge(){
    QString content;
    content.append("文件路径:\t"+file_path_+"\n");
    content.append("宽x高:\t");
    content.append(QString::number(width_));
    content.append('x');
    content.append(QString::number(height_));
    content.append("\n");
    content.append("时长:\t");
    uint32_t duration = static_cast<uint64_t> (duration_);
    uint32_t min = duration/60;
    uint32_t sec = duration%60;
    content.append(QString::number(min));
    content.append(":");
    content.append(QString::number(sec));
    content.append("\n");
    content.append("大小:\t");
    content.append(QString::number(size_));
    content.append("Bytes(");
    content.append(Util::GetHumanReadable(size_));
    content.append(")");
    content.append("\n");
    return content;
}

QString VedioInfo::RecommendSize(){
    if((width_%3==0)&&(height_%3==0)){
        return QString::number(width_/3)+"x"+QString::number(height_/3);
    }else if((width_%2==0)&&(height_%2==0)){
        if((width_%2)>800){
            if((width_%4==0)&&(height_%4==0)){
                return QString::number(width_/4)+"x"+QString::number(height_/4);
            }
        }
        return QString::number(width_/2)+"x"+QString::number(height_/2);
    }else{
        return "";
    }
}

