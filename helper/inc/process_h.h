//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_PROCESS_H_H
#define OS_CD_PROCESS_H_H
extern "C" {
#include "core.h"
};
#include "string"
#include "vector"

namespace fox {

        void                 programCommit(std::vector<Program> &queue);
        std::vector<Program> programVec(const std::string &FilePath);
}  // namespace fox

#endif  // OS_CD_PROCESS_H_H
