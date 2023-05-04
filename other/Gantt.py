import matplotlib.pyplot as plt
import numpy as np
import json

plt.rcParams["font.sans-serif"] = ["SimHei"]

out = open("test/out.json")
outjson = json.load(out)
pidlist = []
instlist = []
io0list = []
io1list = []
namelist = []
piddict = {}
length = len(outjson)
for e in outjson:
    namelist.append(e["name"])
    pidlist.append(int(e["pid"]))
    instlist.append(e["inst"])
    io0list.append(e["io(0)"])
    io1list.append(e["io(1)"])
    piddict[int(e["pid"])] = e["name"]
#
pid_sort = list(set(pidlist))
pid_sort.remove(0)
name_sort = list(set(namelist))
name_sort.remove("*")
name_sort.sort()
#
pid_n = len(pid_sort)
name_n = len(name_sort)
height = name_n + 1

fig, ax = plt.subplots(figsize=(12, 5), dpi=130)
plt.title("RR调度Gantt图")
ax.set_xlabel("时间")
ax.set_ylabel("进程名称")
ax.set_xlim(left=0)
ax.set_ylim(bottom=0, top=pid_n + 1)
ax.set_xticks(np.arange(0, length + 1, 1))
ax.tick_params("x", labelsize=6)
ax.tick_params("y", labelsize=15)
ax.set_yticks(np.arange(0, height, 1))

scale = range(1, height)
ax.set_yticks(scale, name_sort)

namedict = {}

for i in range(len(name_sort)):
    namedict[name_sort[i]] = i + 1


print(namedict, piddict)


p = 0
vl = []
for i in range(length):
    x = np.linspace(i, i + 1, 100)
    pid = pidlist[i]
    io0e = io0list[i]
    io1e = io1list[i]
    if pid != 0:
        if p != pid:
            p = pid
            vl.append(i)
        y = namedict[namelist[i]]
        ax.plot([i, i + 1], [y, y], "-", lw=2, color="r")
    else:
        ax.axvspan(i, i + 1, 0, pid_n + 1, color="c", alpha=0.3)
    if io0e != "*":
        ax.plot(
            [i, i + 1],
            [namedict[piddict[int(io0e)]], namedict[piddict[int(io0e)]]],
            "--",
            lw=2,
            color="b",
        )
    if io1e != "*":
        ax.plot(
            [i, i + 1],
            [namedict[piddict[int(io1e)]], namedict[piddict[int(io1e)]]],
            "--",
            lw=2,
            color="g",
        )
ax.vlines(vl, 0, height, linestyles="dashed",alpha=0.3)
plt.show()
