#ifndef IMAGECROPPERSCENE_HPP
#define IMAGECROPPERSCENE_HPP

#include "qgraphicsitem.h"
#include "resizablerectitem.hpp"
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QRubberBand>

// https://www.qtcentre.org/threads/38990-Graphics-View-mouse-events
class ImageCropperScene : public QGraphicsScene {
    Q_OBJECT
    QGraphicsLineItem *item;

    public:
        ImageCropperScene(QObject *parent = nullptr);
        ~ImageCropperScene();
        void createRubberBand();
        void setScaleFactor(double scaleFactor);
        void setScaleFactor(double maxHeight, double maxWidth, double height, double width);
        void setImage(QString filePath);
        QRubberBand *rubberBand = nullptr;
    signals:
    public slots:
    protected:
//        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    private:
        void selectionChanged();
        double scaleFactor = 1;
        QString imageFilePath = "";
        QPoint origin;
        QPoint endPoint;
//        ResizableRectItem rubberBandItem;
};

#endif // IMAGECROPPERSCENE_HPP
