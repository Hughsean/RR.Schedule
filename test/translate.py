# coding:utf-8
import re


def translate(inst: str, d: dict):
    llll = []
    for line in inst.splitlines():
        line = line.strip()
        if len(line) == 0:
            continue
        items = re.split(r"[ ]+", line)
        op, n = d[items[0]]
        llll.append(op)
        for i in range(0, n):
            llll.append(int(items[i + 1]))
        llll += [0 for i in range(3 - n)]
    return llll


# * op=0, mov : [r1]=[r2]
# * op=1, movi: [r1]=r2
# * op=2, add : [r1]=[r2]+[r3]
# * op=3, addi: [r1]=[r2]+r3
# * op=4, int : cpu.ur[0](r0)与cpu.ur[1](r1)传递参数, 调用iv[INT]中断函数.
# * r0=0:认为IO调用, 进程阻塞, 通过r1进行设备选择; r0=1: 认为进程退出

DICT = {"mov": (0, 2), "movi": (1, 2), "add": (2, 3), "addi": (3, 3), "int": (4, 0)}

if __name__ == "__main__":
    s1 = r"""
        movi 3 15
        movi 4 15
        add  2 3 4
        mov  7 2
        movi 0 0
        movi 1 0
        int
        movi 0 1
        int
        """
    # s1预期结果: 0-7寄存器: 1,0,30,15,15,0,0,30
    s2 = r"""
        movi 3 20
        movi 4 20
        add  2 3 4
        addi 2 2 20
        mov  7 2
        movi 0 0
        movi 1 1
        int
        addi 2 2 20
        movi 0 1
        int
        """
    # s2预期结果: 0-7寄存器: 1,1,80,20,20,0,0,60
    print(translate(s1, DICT))
    print(translate(s2, DICT))
