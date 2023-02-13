#define KB
extern "C" {
#include "core.h"
}
#include "fstream"
#include "helper.h"
#include "iostream"
#include "json/json.h"
int main() {
        std::fstream fos;
        fos.open("./out.txt", std::ios_base::out);
        std::ostream &os = std::cout;
        init();
        //         clock_g();
        Process p{};
        PCB     PP{ .pro = &p };
        PP.prt = M;

        //         PP.state=RUNNING;

        print_tittle(std::cout);
        show_pcb(std::cout, &PP);

        std::cout << "poweroff\n" << std::endl;
}
void f() {
        std::string filename = "./test/test.json";
        // 1.打开文件
        std::ifstream ifile;
        ifile.open(filename);
        if (!ifile.is_open()) {
                return;
        }
        // 2.创建json读工厂对象
        Json::CharReaderBuilder ReaderBuilder;
        ReaderBuilder["emitUTF8"] =
            true;  // utf8支持，不加这句，utf8的中文字符会编程\uxxx

        // 3.创建json对象，等会要返回这个对象
        Json::Value root;

        // 4.把文件转变为json对象，要用到上面的三个变量,数据写入root
        std::string strerr;
        bool        ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
        if (!ok) {
                std::cerr << "json解析错误";
        }
        std::cout << root.size();
}
