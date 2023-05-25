//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_PROCESS_H_H
#define OS_CD_PROCESS_H_H
#include "core.h"
#include "string"
#include "vector"

namespace rr {
        void                 programCommit(std::vector<Program> &queue);
        std::vector<Program> programVec(const std::string &FilePath);
        bool                 programFinish(const std::vector<Program> &vec);
}  // namespace fox

#endif  // OS_CD_PROCESS_H_H
