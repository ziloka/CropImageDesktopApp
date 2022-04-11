// https://stackoverflow.com/questions/46049009/qt-get-mouse-clicked-position-relative-to-image-in-a-graphics-view
// https://stackoverflow.com/a/46065876
// https://github.com/eyllanesc/stackoverflow/blob/master/questions/46049009/main.cpp

#include "include/imagecropperscene.hpp"
#include "qdebug.h"

#include <QGraphicsItem>
#include <QFileDialog>

ImageCropperScene::ImageCropperScene(QObject *parent, QPixmap *image) : QGraphicsScene(parent) {
    qDebug() << "Image Height" << image -> height();
    qDebug() << "Image Width" << image -> width();
    this->image = image;
}

ImageCropperScene::~ImageCropperScene() {

}

void ImageCropperScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
//    item = new QGraphicsLineItem;
//    item->setVisible(false);
//    addItem(item);
//    const QPointF p = mouseEvent->scenePos();
//    item -> setPos(p);
    item = new QGraphicsLineItem;
//    item -> setVisible(true);
    addItem(item);
    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
    QLineF l = item -> line();
    l.setP1(p);
    item -> setLine(l);

//    qDebug() << "onMousePressEvent";
//    qDebug() << "start x" << p.x();
//    qDebug() << "start y" << p.y();
}

void ImageCropperScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
    QLineF l = item -> line();
    l.setP2(p);
    item->setLine(l);
}

void ImageCropperScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
    QLineF l = item -> line();
    l.setP2(p);
    item->setLine(l);

    qDebug() << "onMouseReleaseEvent";
    qDebug() << "start x" << item -> line() . p1().x();
    qDebug() << "start y" << item -> line() . p1().y();
    qDebug() << "end x" << item-> line() .p2().x();
    qDebug() << "end y" << item-> line() .p2().y();

    double xPos1 = item -> line().p1().x();
    double xPos2 = item -> line().p2().x();
    double yPos1 = item -> line().p2().y();
    double yPos2 = item -> line().p2().y();

    double biggerX = 0;
    double smallerX = 0;
    double biggerY = 0;
    double smallerY = 0;

    // figure out what is big and what is small
    if (xPos1 < xPos2) {
        biggerX = xPos2;
        smallerX = xPos1;
    } else {
        biggerX = xPos2;
        smallerX = xPos1;
    }

    if (yPos1 < yPos2) {
        biggerY = yPos1;
        smallerY = yPos2;
    } else {
        biggerX = yPos1;
        smallerY = yPos2;
    }

    qDebug() << "Crop Image X" << smallerX;
    qDebug() << "Crop Image Y" << smallerY;
    qDebug() << "Crop Image Width" << biggerX-smallerX;
    qDebug() << "Crop Image Height" << biggerY-smallerY;

    // https://i.stack.imgur.com/BDHET.png
    // https://stackoverflow.com/questions/7010611/how-can-i-crop-an-image-in-qt
    QRect rect(
        smallerX,
        smallerY,
        biggerX-smallerX,
        smallerY-biggerY
    );

    QPixmap cropped = this->image->copy(rect);

//    qDebug() << "Cropped Image Height" << cropped.height();
//    qDebug() << "Cropped Image Width" << cropped.width();

//    cropped.save("cropped_image.jpg");

}
