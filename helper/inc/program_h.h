//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_PROCESS_H_H
#define OS_CD_PROCESS_H_H
#include "interface.h"
#include "string"
#include "vector"

namespace rr {
        void                   programCommit(std::vector<Program_p> &queue);
        std::vector<Program_p> programVec(const std::string &FilePath);
        bool                   programFinish(const std::vector<Program_p> &vec);
}  // namespace rr

#endif  // OS_CD_PROCESS_H_H
