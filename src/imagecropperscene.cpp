#include "include/imagecropperscene.hpp"
#include "qdebug.h"

#include <QGraphicsItem>

ImageCropperScene::ImageCropperScene(QObject *parent, QPixmap *image) : QGraphicsScene(parent) {
    this->image = image;
}

ImageCropperScene::~ImageCropperScene() {

}

void ImageCropperScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    clickMousePosition[0] = mouseEvent -> scenePos().x();
    clickMousePosition[1] = mouseEvent -> scenePos().y();
    qDebug() << "Got here";
    for (int i = 0; i < 2; i++) {
        qDebug() << clickMousePosition[i];
    }
}

void ImageCropperScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    std::vector<int> endingVector;
    releaseMousePosition[0] = mouseEvent -> scenePos().x();
    releaseMousePosition[1] = mouseEvent -> scenePos().y();
    qDebug() << "Mouse was released";

    // crop logic here?
    // do crop logic
    QRect rect(0, 0, 0, 0);
    QPixmap cropped = this -> image -> copy(rect);

}
