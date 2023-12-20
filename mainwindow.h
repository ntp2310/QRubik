#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainterPath>
#include "openglwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void on_currentColor_currentIndexChanged(int index);

    void on_checkBox_clicked(bool checked);

    void on_camera_released();

    void on_solve_released();

    void on_execute_released();

    void on_pause_released();

    void on_facedir_released();

    void on_text_change();

    Ui::MainWindow *ui;

    OpenGLWindow *glWindow;
    QWidget *glWidget;
};
#endif // MAINWINDOW_H

