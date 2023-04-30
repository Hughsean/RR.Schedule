//
// Created by xSeung on 2023/4/30.
//

#ifndef OS_CD_WINDOW_H
#define OS_CD_WINDOW_H

#include <QWidget>

namespace oscd {
        QT_BEGIN_NAMESPACE
        namespace Ui {
                class window;
        }
        QT_END_NAMESPACE

        class window : public QWidget {
                Q_OBJECT

            public:
                explicit window(QWidget *parent = nullptr);
                ~window() override;

            private:
                Ui::window *ui;
        };
}  // namespace oscd

#endif  // OS_CD_WINDOW_H
