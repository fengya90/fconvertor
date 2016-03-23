#include "util.h"
#include <QString>
Util::Util()
{

}

QString Util::GetHumanReadable(uint64_t size){
    uint64_t ret = size;
    if(ret<1024){
        return QString::number(ret)+" B";
    }
    ret = ret/1024;
    if(ret<1024){
        return QString::number(ret)+" KB";
    }
    ret = ret/1024;
    if(ret<1024){
        return QString::number(ret)+" MB";
    }
    ret = ret/1024;
    if(ret<1024){
        return QString::number(ret)+" GB";
    }
    return "";
}

