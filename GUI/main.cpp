#include "QApplication"
#include "QPushButton"
#include "ui/window.h"

int main(int argc, char *argv[]) {

        QApplication a(argc, argv);
        auto         b = new ui::window;
        auto         c = b->findChild<QPushButton *>();

        if (c!= nullptr){
        }

        b->show();
        return QApplication::exec();
}
