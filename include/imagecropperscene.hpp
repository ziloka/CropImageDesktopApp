#ifndef IMAGECROPPERSCENE_HPP
#define IMAGECROPPERSCENE_HPP

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>

#include "qwidget.h"

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
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    private:
        QString imageFilePath;
};

#endif // IMAGECROPPERSCENE_HPP
