#ifndef UTIL_H
#define UTIL_H

#include <QString>
class Util
{
public:
    Util();
    static  QString program_ffprobe(){return "/Users/fengya/Downloads/ffmpeg/ffprobe";}
    static  QString program_ffmpeg(){return "/Users/fengya/Downloads/ffmpeg/ffmpeg";}
    static QString GetHumanReadable(uint64_t size);
};

#endif // UTIL_H
