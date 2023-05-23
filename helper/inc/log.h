//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_LOG_H
#define OS_CD_LOG_H
extern "C" {
#include "core.h"
};
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

        using jsondict = std::map<std::string, std::string>;
        std::string summary(const std::vector<Program> &vec);
        Info        infoFetch();
        jsondict    log(std::ostream &os);
        void        urlog(std::ostream &os);
        jsondict    infoextract(const Info &info);
        std::string translate(void *p, int pc);
        void        jsonoutput(std::ostream &os, const std::vector<jsondict> &dicts);
}  // namespace rr
#endif  // OS_CD_LOG_H
