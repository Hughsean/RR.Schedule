# coding:utf-8
import re
from json.encoder import JSONEncoder as ec


# * op=0, mov : [r1]=[r2]
# * op=1, movi: [r1]=r2
# * op=2, add : [r1]=[r2]+[r3]
# * op=3, addi: [r1]=[r2]+r3
# * op=4, int : cpu.ur[0](r0)与cpu.ur[1](r1)传递参数, 调用iv[INT]中断函数.
# * r0=0:认为IO调用, 进程阻塞, 通过r1进行设备选择; r0=1: 认为进程退出

DICT = {"mov": (0, 2), "movi": (1, 2), "add": (2, 3), "addi": (3, 3), "int": (4, 0)}


class Program:
    def __init__(self, name: str, inst: str, io: int, at: int) -> None:
        self.name = name
        self.inst = inst
        self.io = io
        self.at = at

    def translate(inst: str, d: dict) -> list:
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

    def todict(self):
        return {
            "name": self.name,
            "address_space": Program.translate(self.inst, DICT),
            "io_time_required": self.io,
            "arrive_time": self.at,
        }


if __name__ == "__main__":
    # len=18
    inst1 = r"""
        movi 3 15   //[3]=15
        movi 4 15   //[4]=15
        add  2 3 4  //[4]=30
        movi 5 0    //[5]=0
        addi 5 5 1  //[5]=1
        addi 5 5 1  //[5]=2
        addi 5 5 1  //[5]=3
        addi 5 5 1  //[5]=4
        addi 5 5 1  //[5]=5
        addi 5 5 1  //[5]=6
        addi 5 5 1  //[5]=7
        addi 5 5 1  //[5]=8
        addi 5 5 1  //[5]=9
        movi 0 0    //[0]=0
        movi 1 0    //[1]=0        
        int         //io系统调用, 设备0
        movi 0 1    //[0]=1
        int         //exit
        """
    # len=12
    inst2 = r"""
        movi 3 20   //[3]=20
        movi 4 20   //[4]=20
        add  2 3 4  //[2]=40
        addi 2 2 20 //[2]=60
        movi 5 0    //[5]=0
        mov  5 2    //[5]=60
        movi 0 0    //[0]=0
        movi 1 1    //[1]=1
        int         //io系统调用, 设备1
        addi 2 2 20 //[2]80
        movi 0 1    //[0]1
        int         //exit
        """
    # len=7
    inst3 = r"""
        movi 0 0    //[0]=0
        movi 1 0    //[1]=1
        int         //io 0
        movi 1 1    //[1]=1
        int         //io 1
        movi 0 1    //[0]=1
        int         //exit
        """
    # name, inst, iotime, arrivetime
    a = Program("A", inst1, 7, 8)
    b = Program("B", inst2, 5, 0)
    c = Program("C", inst3, 8, 15)
    d = Program("D", inst3, 3, 20)
    e = Program("E", inst2, 5, 4)
    f = Program("F", inst1, 10, 11)

    outjson = ec().encode(
        [a.todict(), b.todict(), c.todict(), d.todict(), e.todict(), f.todict()]
    )
    with open("test/programs.jsonc", "w") as out:
        out.write(outjson)
