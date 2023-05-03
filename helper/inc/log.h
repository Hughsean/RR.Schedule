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

namespace fox {
        using Info = struct info_ {
                const Kernel    *kernel;
                const CPU       *cpu;
                const IO_Device *io_devide;
        };

        using jsondict = std::map<std::string, std::string>;

        Info        infoFetch();
        void        log(std::ostream &os);
        jsondict    infoextract(const Info &info);
        std::string translate(void *p, int pc);
}  // namespace fox
#endif  // OS_CD_LOG_H
