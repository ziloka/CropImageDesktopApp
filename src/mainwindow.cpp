#include "include/mainwindow.hpp"
#include "include/imagecropperscene.hpp"
#include "ui_mainwindow.h"

#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setMouseTracking(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    // https://stackoverflow.com/questions/3941917/can-the-open-file-dialog-be-used-to-select-a-folder
    // https://stackoverflow.com/a/10616741
    QString folder = QFileDialog::getExistingDirectory(this, tr("Open directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QDir directory(folder);
    currentDirectory = folder;
    // clear items in listWidget
    ui -> listWidget -> clear();
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.jpeg" << ".JPEG" << "*.png" << "*.PNG" << "*.webp" << "*.WEPB", QDir::Files);
    for (int i = 0; i < images.length(); i++) {
        ui -> listWidget -> insertItem(i, images.at(i));
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    QString filePath = currentDirectory + QDir::separator() + (item -> text());
    // load the image
    // https://forum.qt.io/topic/130073/view-an-image-on-qgraphicsview-from-resources
    QPixmap image(filePath);
    if (ui->graphicsView->scene()) ui->graphicsView->scene()->clear();

    ImageCropperScene *scene = new ImageCropperScene(this, filePath);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->scene()->addPixmap(image);
    // https://forum.qt.io/topic/9652/solved-drawing-on-top-of-an-image/5
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    // https://stackoverflow.com/questions/17028680/qt5-c-qgraphicsview-images-dont-fit-view-frame
    // https://stackoverflow.com/a/17085612
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
}


