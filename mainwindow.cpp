#include "mainwindow.hpp"
#include "customscene.hpp"
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
        scene = new CustomScene(this);
        ui->graphicsView->setScene(scene);
    } else {
        ui->graphicsView->scene()->clear();
    }

//    QPixmap scaled = image.scaled(QSize(ui->graphicsView->scene()->sceneRect().width(), ui->graphicsView->scene()->sceneRect().height()), Qt::KeepAspectRatio, Qt::SmoothTransformation);

//    qDebug() << "graphicview x: " << scaled.height();
//    qDebug() << "graphicsview y: " << scaled.width();

    // set the image (the image file path to the image that was clicked on)
//    ui->graphicsView->scene()->addPixmap(scaled);
    ui->graphicsView->scene()->addPixmap(image);

    ui->graphicsView->scene()->setSceneRect(QRect(0, 0, image.width(), image.height()));

    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

//    ui->graphicsView->setFixedWidth(image.width());
//    ui->graphicsView->setFixedHeight(image.height());
    // https://github.com/sashoalm/ResizableRectItem#sample-usage
    QBrush brush(QColor(255, 0, 0, 255/3));
    ResizableRectItemSettings *settings = new ResizableRectItemSettings(
        1,
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
    //interactiveRectangle->setParentItem(getImageFromScene());

    scene->addItem(interactiveRectangle);

    // https://stackoverflow.com/questions/17028680/qt5-c-qgraphicsview-images-dont-fit-view-frame
    // https://stackoverflow.com/a/17085612
    ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
    ui->graphicsView->setRenderHint(QPainter::RenderHint::Antialiasing);

    // set scale factor
    //What will happen if fit by width?
    dynamic_cast<CustomScene*>(scene)->setScaleFactor((double) ui->graphicsView->height()/(double) image.height());
}

QGraphicsPixmapItem* MainWindow::getImageFromScene() {
    QGraphicsPixmapItem *image = nullptr;
    foreach (QGraphicsItem *item, this->ui->graphicsView->scene()->items()) {
        QGraphicsPixmapItem *tempImage = qgraphicsitem_cast<QGraphicsPixmapItem *>(item);
        if (tempImage){
            image = tempImage;
            break;
        }
    }
    return image;
}

ResizableRectItem* MainWindow::getRectItemFromScene() {
    ResizableRectItem *rectItem = nullptr;
    foreach (QGraphicsItem *item, ui->graphicsView->scene()->items()) {
        ResizableRectItem *tempRectItem = qgraphicsitem_cast<ResizableRectItem *>(item);
        if(tempRectItem) {
            rectItem = tempRectItem;
            break;
        }
    }
    return rectItem;
}

void MainWindow::on_cropButton_clicked()
{
    // user clicked on crop button without selecting an image
    if(!ui->graphicsView->scene()) return;

    QGraphicsPixmapItem *image = getImageFromScene();
    ResizableRectItem *rectItem = getRectItemFromScene();

    QGraphicsScene *scene = ui->graphicsViewResult->scene();
    if(!scene) {
        scene = new QGraphicsScene(this);
        ui->graphicsViewResult->setScene(scene);
    } else {
        ui->graphicsViewResult->scene()->clear();
    }

    scene->addPixmap(image->pixmap().copy(rectItem->mapToScene(rectItem->boundingRect()).boundingRect().toRect()));
    ui->graphicsViewResult->fitInView(ui->graphicsViewResult->scene()->sceneRect(), Qt::KeepAspectRatio);
}

void resizeRect(ResizableRectItem *rectItem, double targetWidth, double targetHeight) {

    QPoint center = rectItem->boundingRect().center().toPoint();

    qDebug() << "target width" << targetWidth;
    qDebug() << "target height" << targetHeight;
    qDebug() << "rectitem center x: " << center.x() << "center y: " << center.y();

    QPoint newTopLeft = QPoint(center.x()-(targetWidth*0.5)-1, center.y()-(targetHeight*0.5)-1);
    QPoint newBottomRight = QPoint(center.x()+(targetWidth*0.5)-1, center.y()+(targetHeight*0.5)-1);

    qDebug() << "top left corner: " << newTopLeft;
    qDebug() << "bottom right corner: " << newBottomRight;

    rectItem->setRect(QRect(newTopLeft, newBottomRight));
}


void MainWindow::on_changeSizeSubmit_clicked()
{
    // user clicked on crop button without selecting an image
    if(!ui->graphicsView->scene()) return;

    QGraphicsPixmapItem *image = getImageFromScene();
    ResizableRectItem *rectItem = getRectItemFromScene();
    QString changeText = ui -> percentageDropdown -> currentText();
    double changeRatio = changeText.replace("%", "").toDouble()/100;
    double targetWidth = image->pixmap().width() * changeRatio;
    double targetHeight = image->pixmap().height() * changeRatio;
    resizeRect(rectItem, targetWidth, targetHeight);
}


void MainWindow::on_imageSizeSubmit_clicked()
{
    // user clicked on crop button without selecting an image
    if(!ui->graphicsView->scene()) return;

    static QRegularExpression re("\\d+", QRegularExpression::CaseInsensitiveOption);

    ResizableRectItem *rectItem = getRectItemFromScene();
    QString choiceText = ui -> imageDropDown -> currentText();
    QRegularExpressionMatchIterator matches = re.globalMatch(choiceText);

    resizeRect(rectItem, matches.next().captured().toDouble(), matches.next().captured().toDouble());
}

