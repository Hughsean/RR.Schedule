#define KB
extern "C" {
#include "core.h"
}
#include "fstream"
#include "iostream"
#include "json/json.h"
#include "fmt/core.h"
#include "helper.h"

int main() {
        //        std::fstream fos;
        //        fos.open("./out.txt", std::ios_base::out);
        //        std::ostream &os = std::cout;
        //        init();
        ////        clock_g();
        //        Process p{};
        //        PCB     PP{ .pro = &p };
        //        PP.prt = M;
        //
        //        //         PP.state=RUNNING;
        //
        //        print_tittle(std::cout);
        //        show_pcb(std::cout, &PP);
        //
        //        std::cout << "poweroff\n" << std::endl;
        //        char i=1<<8;
        //        void *p= malloc(1024);
        //        free(p);
        //        std::cout << std::hex <<(int)i << std::endl;
        init();
}
void f() {
        std::string filename = "./test/test.json";
        // 1.���ļ�
        std::ifstream ifile;
        ifile.open(filename);
        if (!ifile.is_open()) {
                return;
        }
        // 2.����json����������
        Json::CharReaderBuilder ReaderBuilder;
        // utf8֧�֣�������䣬utf8�������ַ�����\uxxx
        ReaderBuilder["emitUTF8"] = true;
        // 3.����json���󣬵Ȼ�Ҫ�����������
        Json::Value root;
        // 4.���ļ�ת��Ϊjson����Ҫ�õ��������������,����д��root
        std::string strerr;
        bool        ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
        if (!ok) {
                std::cerr << "json��������";
        }
        std::cout << root.size();
        std::stoi("12");
}
