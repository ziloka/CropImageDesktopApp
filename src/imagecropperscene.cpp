// https://stackoverflow.com/questions/46049009/qt-get-mouse-clicked-position-relative-to-image-in-a-graphics-view
// https://stackoverflow.com/a/46065876
// https://github.com/eyllanesc/stackoverflow/blob/master/questions/46049009/main.cpp

#include "include/mainwindow.hpp"
#include "include/imagecropperscene.hpp"
#include "qdebug.h"

#include <cmath>

#include <QGraphicsItem>
#include <QFileDialog>

ImageCropperScene::ImageCropperScene(QObject *parent, QString imageFilePath) : QGraphicsScene(parent) {
    this->imageFilePath = imageFilePath;
}

ImageCropperScene::~ImageCropperScene() {

}

void ImageCropperScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    item = new QGraphicsLineItem;
    item -> setVisible(false);
    addItem(item);
    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
    QLineF l = item -> line();
    l.setP1(p);
    item -> setLine(l);
}

void ImageCropperScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
    QLineF l = item -> line();
    l.setP2(p);
    item->setLine(l);
}

void ImageCropperScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QPixmap image(this->imageFilePath);
    const QPointF p = item -> mapFromScene(mouseEvent -> scenePos());
    QLineF l = item -> line();
    l.setP2(p);
    item->setLine(l);

    double xPos1 = item -> line().p1().x();
    double xPos2 = item -> line().p2().x();
    double yPos1 = item -> line().p1().y();
    double yPos2 = item -> line().p2().y();

    // https://i.stack.imgur.com/BDHET.png
    // https://stackoverflow.com/questions/7010611/how-can-i-crop-an-image-in-qt
    QRect rect(
       fmin(xPos1, xPos2),
       fmin(yPos1, yPos2),
       abs(xPos1-xPos2),
       abs(yPos1-yPos2)
    );

    QPixmap cropped = image.copy(rect);

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save Cropped Image", QDir::currentPath(), QObject::tr("All files (*.*)"));

    cropped.save(fileName);

}
