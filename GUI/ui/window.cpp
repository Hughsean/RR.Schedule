//
// Created by xSeung on 2023/4/7.
//

// You may need to build the project (run Qt uic code generator) to get "ui_window.h"
// resolved

#include "window.h"
#include "ui_window.h"

namespace ui {
        window::window(QWidget *parent) : QMainWindow(parent), ui(new Ui::window) {
                ui->setupUi(this);
        }

        window::~window() {
                delete ui;
        }
}  // namespace ui
