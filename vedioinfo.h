#ifndef VEDIOINFO_H
#define VEDIOINFO_H

#include <stdint.h>
#include <QString>

class VedioInfo
{
public:
    VedioInfo();
    bool Parse(QString file_path);
    QString ToQString();
    QString RecommendSize();
    QString file_path(){return file_path_;}
private:
    QString file_path_;
    uint32_t width_;
    uint32_t height_;
    double duration_;
    uint64_t size_;
    bool parse_ok_;
};

#endif // VEDIOINFO_H
