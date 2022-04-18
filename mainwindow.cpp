#include "mainwindow.hpp"
#include "qgraphicssceneevent.h"
#include "qgraphicsview.h"
#include "ui_mainwindow.h"
#include "resizablerectitemsettings.hpp"
#include "resizablerectitem.hpp"
#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setMouseTracking(true);

    // just for development purposes only
    QString folder = "C:\\Users\\Connor\\Downloads\\jpg images";
    QDir directory(folder);
    currentDirectory = folder;
    // clear items in listWidget
    ui -> listWidget -> clear();
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.jpeg" << ".JPEG" << "*.png" << "*.PNG" << "*.webp" << "*.WEPB", QDir::Files);
    for (int i = 0; i < images.length(); i++) {
        ui -> listWidget -> insertItem(i, images.at(i));
    }
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
    // https://doc.qt.io/qt-5/qimage.html#reading-and-writing-image-files
    QStringList images = directory.entryList(QStringList() << "*.jpg" << "*.JPG" << "*.jpeg" << ".JPEG" << "*.png" << "*.PNG" << "*.webp" << "*.WEPB", QDir::Files);
    for (int i = 0; i < images.length(); i++) {
        ui -> listWidget -> insertItem(i, images.at(i));
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item) {
    // load the image
    // https://forum.qt.io/topic/130073/view-an-image-on-qgraphicsview-from-resources
    QPixmap image(currentDirectory + QDir::separator() + (item->text()));

    QGraphicsScene *scene = ui->graphicsView->scene();

    if(!scene) {
        scene = new QGraphicsScene(this);
        ui->graphicsView->setScene(scene);
    } else {
        ui->graphicsView->scene()->clear();
    }

    // set the image (the image file path to the image that was clicked on)
    ui->graphicsView->scene()->addPixmap(image);

    ui->graphicsView->scene()->setSceneRect(QRect(0, 0, image.width(), image.height()));

    // https://github.com/sashoalm/ResizableRectItem#sample-usage
    QBrush brush(QColor(255, 0, 0, 255/3));
    ResizableRectItemSettings *settings = new ResizableRectItemSettings(
        5,
        QSizeF(30, 30),
        QSizeF(image.width(), image.height()),
        Qt::DashLine,
        brush
    );

    ResizableRectItem *interactiveRectangle = new ResizableRectItem(
        QRectF(
            QPointF(
                image.width()*0.25,
                image.height()*0.25
            ),
           QPointF(
                image.width()*0.75,
                image.height()*0.75
           )
        ),
        settings
    );
    interactiveRectangle->setBrush(brush);
    interactiveRectangle->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(interactiveRectangle);

    // https://stackoverflow.com/questions/17028680/qt5-c-qgraphicsview-images-dont-fit-view-frame
    // https://stackoverflow.com/a/17085612
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->setRenderHint(QPainter::RenderHint::Antialiasing);
}


void MainWindow::on_pushButton_clicked()
{
    QGraphicsPixmapItem *image = nullptr;
    ResizableRectItem *rectItem = nullptr;

    // user clicked on crop button without selecting an image
    if(!ui->graphicsView->scene()) return;

    foreach (QGraphicsItem *item, ui->graphicsView->scene()->items()) {
        QGraphicsPixmapItem *tempImage = qgraphicsitem_cast<QGraphicsPixmapItem *>(item);
        ResizableRectItem *tempRectItem = qgraphicsitem_cast<ResizableRectItem *>(item);
        if (tempImage) image = tempImage;
        else if(tempRectItem) rectItem = tempRectItem;
        else if (image && rectItem) break;
    }

    //QPointF vec = image->mapToItem(rectItem, 0, 0);
    //qDebug() << "vector: " << vec;
    qDebug() << "rect: " << rectItem->mapToScene(rectItem->boundingRect()).boundingRect().toRect();

    QPixmap cropped = image->pixmap().copy(rectItem->mapToScene(rectItem->boundingRect()).boundingRect().toRect());
//    QPixmap cropped = image->pixmap().copy(rectItem->boundingRect().toRect());

    QGraphicsScene *scene = ui->graphicsViewResult->scene();

    if(!scene) {
        scene = new QGraphicsScene(this);
        ui->graphicsViewResult->setScene(scene);
    } else {
        ui->graphicsViewResult->scene()->clear();
    }
    scene->addPixmap(cropped);

    ui->graphicsViewResult->fitInView(ui->graphicsViewResult->scene()->sceneRect(), Qt::KeepAspectRatio);
}

