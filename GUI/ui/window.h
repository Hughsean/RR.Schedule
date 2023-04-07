//
// Created by xSeung on 2023/4/7.
//

#ifndef OS_CD_WINDOW_H
#define OS_CD_WINDOW_H

#include <QMainWindow>

namespace ui {
        QT_BEGIN_NAMESPACE
        namespace Ui {
                class window;
        }
        QT_END_NAMESPACE

        class window : public QMainWindow {
                Q_OBJECT

            public:
                explicit window(QWidget *parent = nullptr);
                ~window() override;

            private:
                Ui::window *ui;
        };
}  // namespace ui

#endif  // OS_CD_WINDOW_H
