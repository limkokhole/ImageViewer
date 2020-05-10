#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (img.isNull()) {
        ui->zoomInButton->setEnabled(false);
        ui->zoomOutButton->setEnabled(false);
        ui->viewLabel->setText("打开一个图片(Ctrl+O)");
    }

    ui->openButton->setShortcut(QKeySequence("Ctrl+O"));

    scaleFactor = 1;

    QMap<int, int> desktop = Util::GetScreenResolution();
    int desktopWidth = desktop.firstKey();
    int desktopHeight = desktop[desktopWidth];
    int factor = 2;
    int w = desktopWidth / factor;
    int h = desktopHeight / factor;
//    qDebug() << "width:" << w << "height:" << h;
    this->resize(w, h);

    setWindowTitle("图片查看器");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 缩放图片的公共函数
void MainWindow::scaleImage(double factor)
{
//    qDebug() << "scaleFactor before" << scaleFactor;
    if ( scaleFactor >= 0.7 && scaleFactor <= 1.5) {
        tmpFactor = scaleFactor;
        QSize size = img.size();
        QSize scaleSize = tmpFactor * size;

        img = img.scaled(scaleSize, Qt::KeepAspectRatio);

        ui->viewLabel->resize(scaleSize);
        ui->viewLabel->setPixmap(img);

        ui->zoomOutButton->setEnabled(true);
        ui->zoomInButton->setEnabled(true);
        scaleFactor *= factor;
    } else if (scaleFactor < 0.7) {
        scaleFactor = tmpFactor;
        ui->zoomInButton->setEnabled(false);
        ui->zoomOutButton->setEnabled(true);
    } else {
        scaleFactor = tmpFactor;
        ui->zoomInButton->setEnabled(true);
        ui->zoomOutButton->setEnabled(false);
    }

    qDebug() << "scaleFactor after" << scaleFactor;
}

void MainWindow::on_zoomOutButton_clicked()
{
    if (img.isNull()) {
        return;
    }
    double factor = 1.25;
    scaleImage(factor);
}

void MainWindow::on_zoomInButton_clicked()
{
    if (img.isNull()) {
        return;
    }
    double factor = 0.8;
    scaleImage(factor);
}

void MainWindow::on_previousButton_clicked()
{

}

void MainWindow::on_nextButton_clicked()
{

}

void MainWindow::on_turnLeftButton_clicked()
{

}

void MainWindow::on_turnRightButton_clicked()
{

}

void MainWindow::on_removeButton_clicked()
{

}

// 打开图片
void MainWindow::on_openButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                                                "打开图片",
                                                "/",
                                                tr("图片文件 (*.png *.jpg)"));
    if (path.isEmpty()) {
        return;
    } else {
        QPixmap tmp(path);
        img = tmp;
        int w = img.width();
        int h = img.height();
        ui->viewLabel->resize(w, h);
        ui->viewLabel->setPixmap(img);

        ui->zoomInButton->setEnabled(true);
        ui->zoomOutButton->setEnabled(true);
    }
}
