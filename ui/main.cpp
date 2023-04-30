#include "QApplication"
#include "window.h"
int main(int argc, char *argv[]) {
        QApplication a(argc, argv);
        oscd::window win;
        win.show();
        return QApplication::exec();
}