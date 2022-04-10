#ifndef IMAGECROPPERSCENE_HPP
#define IMAGECROPPERSCENE_HPP

#endif // IMAGECROPPERSCENE_HPP

#include <vector>

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>

// https://www.qtcentre.org/threads/38990-Graphics-View-mouse-events

class ImageCropperScene : public QGraphicsScene {
    Q_OBJECT
    public:
        ImageCropperScene(QObject *parent = nullptr, QPixmap *image = nullptr);
        ~ImageCropperScene();
    signals:
    public slots:
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    private:
        QPixmap *image;
        int clickMousePosition[2];
        int releaseMousePosition[2];
};
