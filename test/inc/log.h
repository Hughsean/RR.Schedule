//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_LOG_H
#define OS_CD_LOG_H
#include "interface.h"
#include "iostream"
#include "map"
#include "string"
#include "vector"

namespace rr {
        using logslice = std::tuple<int, std::string, int, std::string, int, std::string, std::string>;
        logslice    log(std::ostream &os);
        void        urlog(std::ostream &os);
        logslice    infoextract();
        std::string translate(void *p, int pc);
        void        jsonoutput(std::ostream &os, const std::vector<logslice> &slices);
}  // namespace rr
#endif  // OS_CD_LOG_H
