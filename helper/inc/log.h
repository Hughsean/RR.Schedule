//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_LOG_H
#define OS_CD_LOG_H
#include "core.h"
#include "iostream"
#include "map"
#include "string"
#include "vector"

namespace rr {
        using Info = struct info_ {
                const Kernel    *kernel;
                const CPU       *cpu;
                const IO_Device *io_devide;
        };
        // clk name pid inst pc io(0) io(1)
        using logslice = std::tuple<int, std::string, int, std::string, int, std::string, std::string>;
        Info        infoFetch();
        logslice    log(std::ostream &os);
        void        urlog(std::ostream &os);
        logslice    infoextract(const Info &info);
        std::string translate(void *p, int pc);
        void        jsonoutput(std::ostream &os, const std::vector<logslice> &slices);
}  // namespace rr
#endif  // OS_CD_LOG_H
