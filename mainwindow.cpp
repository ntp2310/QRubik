#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->currentColor->addItem("Blue");
    ui->currentColor->addItem("Green");
    ui->currentColor->addItem("Yellow");
    ui->currentColor->addItem("White");
    ui->currentColor->addItem("Red");
    ui->currentColor->addItem("Orange");

    this->ui->textEdit->setReadOnly(true);

    glWindow = new OpenGLWindow();

    QSurfaceFormat format;
    format.setSamples(8);
    format.setDepthBufferSize(24);
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setStencilBufferSize(8);
    format.setVersion(2, 1);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setOptions(QSurfaceFormat::DeprecatedFunctions);
    format.setSwapInterval(0);
    glWindow->setFormat(format);

    glWidget = QWidget::createWindowContainer(glWindow, ui->centralwidget);
/*
    QPainterPath path;
    path.addRoundedRect(glWidget->rect(), 40, 40);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    ui->GLwidget->setMask(mask);
*/
    glWidget->setEnabled(true);
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(glWidget->sizePolicy().hasHeightForWidth());
    glWidget->setSizePolicy(sizePolicy);
    glWidget->setMinimumSize(QSize(600, 500));

    //glWidget->setStyleSheet(QString::fromUtf8("border-style: solid;\n"));


    ui->horizontalLayout->replaceWidget(ui->GLwidget, glWidget);

    delete ui->GLwidget;

    connect(ui->currentColor, &QComboBox::currentIndexChanged, this, &MainWindow::on_currentColor_currentIndexChanged);
    connect(ui->checkBox, &QCheckBox::clicked, this, &MainWindow::on_checkBox_clicked);
    connect(ui->camera, &QPushButton::released, this, &MainWindow::on_camera_released);
    connect(ui->solve, &QPushButton::released, this, &MainWindow::on_solve_released);
    connect(ui->execute, &QPushButton::released, this, &MainWindow::on_execute_released);
    connect(ui->pause, &QPushButton::released, this, &MainWindow::on_pause_released);
    connect(ui->facedir, &QCheckBox::released, this, &MainWindow::on_facedir_released);
    connect(glWindow, &OpenGLWindow::frameSwapped, this, &MainWindow::on_text_change);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentColor_currentIndexChanged(int index)
{
    this->glWindow->currentColor = index;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    this->glWindow->configMode = checked;
}

void MainWindow::on_solve_released()
{
    this->glWindow->solve();
    this->ui->textEdit->setText(tr(this->glWindow->sol));
}

void MainWindow::on_camera_released()
{
    this->glWindow->inputByCamera();
}

void MainWindow::on_execute_released()
{
    this->glWindow->execute = true;
    this->glWindow->pause = false;
    this->ui->pause->setEnabled(true);
}

void MainWindow::on_pause_released()
{
    this->glWindow->pause = true;
    this->ui->pause->setEnabled(false);
}

void MainWindow::on_facedir_released()
{
    this->glWindow->facedir = !this->glWindow->facedir;
}

void MainWindow::on_text_change()
{
    if (this->glWindow->execute)
        this->ui->textEdit->setText(this->glWindow->solution);
}

