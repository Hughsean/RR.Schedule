 #define KB
 extern "C" {
 #include "core.h"
 }
 #include "fstream"
 #include "helper.h"
 #include "iostream"

 int main() {
         std::fstream fos;
         fos.open("./out.txt", std::ios_base::out);
         std::ostream &os = std::cout;
         init();
         clock_g();
         pid_alloc();
         pid_alloc();
         Process s{};
         PCB     p{ .pid = pid_alloc(), .prt = H, .pro = &s };
         PCB     q{ .pid = pid_alloc(), .pro = &s, .next = &p };
         show_pcblist(os, &q);
         store_regs(&p);
         std::cout << "poweroff\n" << std::endl;
 }
