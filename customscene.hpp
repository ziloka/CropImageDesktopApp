#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP

#include <QGraphicsScene>

class CustomScene : public QGraphicsScene {
    Q_OBJECT
public:
    CustomScene(QObject *parent);
    void setScaleFactor(double scaleFactor);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    double scaleFactor = 1;
};

#endif // CUSTOMSCENE_HPP
