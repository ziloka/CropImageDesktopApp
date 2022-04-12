#ifndef IMAGECROPPERSCENE_HPP
#define IMAGECROPPERSCENE_HPP


#endif // IMAGECROPPERSCENE_HPP

#include <vector>
#include "qwidget.h"
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>

// https://www.qtcentre.org/threads/38990-Graphics-View-mouse-events

class ImageCropperScene : public QGraphicsScene {
    Q_OBJECT
    QGraphicsLineItem *item;

    public:
        ImageCropperScene(QObject *parent = nullptr, QString filePath = "");
        ~ImageCropperScene();
    signals:
    public slots:
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
//        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    private:
        QString imageFilePath;
};
