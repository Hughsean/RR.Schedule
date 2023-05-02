//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_LOG_H
#define OS_CD_LOG_H
extern "C" {
#include "core.h"
};
#include "iostream"
#include "string"

namespace fox
{
        using Info = struct info_ {
                const Kernel    *kernel;
                const CPU       *cpu;
                const IO_Device *io_devide;
        };

        Info        infoFetch();
        void        log(std::ostream &os);
        std::string format(const Info &info);
        std::string translate(Info info);
}  // namespace fox
#endif  // OS_CD_LOG_H
