#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDir>
extern QString cmd_path;

class Util
{
public:
    Util();
    static  QString program_ffprobe(){return cmd_path+QDir::separator()+"ffprobe";}
    static  QString program_ffmpeg(){return  cmd_path+QDir::separator()+"ffmpeg";}
    static QString GetHumanReadable(uint64_t size);
};

#endif // UTIL_H
