// https://stackoverflow.com/questions/46049009/qt-get-mouse-clicked-position-relative-to-image-in-a-graphics-view
// https://stackoverflow.com/a/46065876
// https://github.com/eyllanesc/stackoverflow/blob/master/questions/46049009/main.cpp

#include "include/mainwindow.hpp"
#include "include/imagecropperscene.hpp"
#include "qdebug.h"
#include "qgraphicsview.h"
#include "qpainter.h"

#include <cmath>

#include <QGraphicsItem>
#include <QFileDialog>

ImageCropperScene::ImageCropperScene(QObject *parent) : QGraphicsScene(parent) {
    QGraphicsView *graphicsViewWidget = parent -> findChild<QGraphicsView*>(QString("graphicsView"), Qt::FindChildrenRecursively);
    if (!rubberBand) rubberBand = new QRubberBand(QRubberBand::Rectangle, graphicsViewWidget);
    rubberBand->setGeometry(
        QRect(
            QPoint(0, 0),
            QPoint(100, 100)
        )
    );
    //rubberBand->show();
}

ImageCropperScene::~ImageCropperScene() {

}

void ImageCropperScene::setImage(QString filePath) {
    imageFilePath = filePath;
}

void ImageCropperScene::setScaleFactor(double factor) {
    scaleFactor = factor;
}

void ImageCropperScene::setScaleFactor(double maxHeight, double maxWidth, double height, double width) {
//    scaleFactor = factor;
    if (height <= maxHeight && width <= maxWidth) {
        scaleFactor = 1;
    } else if (height < maxHeight && width > maxWidth) {
        scaleFactor = maxWidth/width;
    } else if (height > maxHeight && width < maxWidth) {
        scaleFactor = maxHeight/height;
    } else {
//        scaleFactor =
    }
}


//void ImageCropperScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
////    origin = QPoint(mouseEvent->scenePos().x()*scaleFactor, mouseEvent->scenePos().y()*scaleFactor);
////    if (!rubberBand) rubberBand = new QRubberBand(QRubberBand::Rectangle, qobject_cast<QWidget*>(this));
////    rubberBand->setGeometry(QRect(origin, QSize()));
////    rubberBand->show();


////    origin = QPoint(mouseEvent->scenePos().x()*scaleFactor, mouseEvent->scenePos().y()*scaleFactor);
////    QGraphicsView *graphicsViewWidget = parent() -> findChild<QGraphicsView*>(QString("graphicsView"), Qt::FindChildrenRecursively);
////    if (!rubberBand) rubberBand = new QRubberBand(QRubberBand::Rectangle, graphicsViewWidget);
////    rubberBand->setGeometry(QRect(origin, QSize()));
////    rubberBand->show();
//}

void ImageCropperScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    endPoint = QPoint(mouseEvent->scenePos().x()*scaleFactor, mouseEvent->scenePos().y()*scaleFactor);
//    qDebug() << origin;
//    qDebug() << endPoint;
    rubberBand->setGeometry(
        QRect(
            fmin(origin.x(), endPoint.x()),
            fmin(origin.y(), endPoint.y()),
            abs(origin.x() - endPoint.x()),
            abs(origin.y() - endPoint.y())
        )
    );
}

void ImageCropperScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {

//    QPixmap image(this->imageFilePath);
//    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
//    QLineF l = item -> line();
//    l.setP2(p);
//    item->setLine(l);

//    double xPos1 = item -> line().p1().x();
//    double xPos2 = item -> line().p2().x();
//    double yPos1 = item -> line().p1().y();
//    double yPos2 = item -> line().p2().y();

//    // https://i.stack.imgur.com/BDHET.png
//    // https://stackoverflow.com/questions/7010611/how-can-i-crop-an-image-in-qt
//    QRect rect(
//       fmin(xPos1, xPos2),
//       fmin(yPos1, yPos2),
//       abs(xPos1-xPos2),
//       abs(yPos1-yPos2)
//    );

//    QPixmap cropped = image.copy(rect);

//    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Cropped Image", QDir::currentPath(), QObject::tr("All files (*.*)"));

//    cropped.save(fileName);

}
