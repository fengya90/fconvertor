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
private:
    uint32_t width_;
    uint32_t height_;
    double duration_;
    uint64_t size_;
    bool parse_ok_;
};

#endif // VEDIOINFO_H
