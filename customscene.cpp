#include "customscene.hpp"
#include "qdebug.h"
#include "resizablerectitem.hpp"

CustomScene::CustomScene(QObject *parent) : QGraphicsScene(parent) {

}

void CustomScene::setScaleFactor(double scaleFactor) {
    this->scaleFactor = scaleFactor;
}

// when the user double clicks the scene the rubberband will move to that position
void CustomScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    ResizableRectItem *rectItem = nullptr;
    foreach (QGraphicsItem *item, this->items()) {
        ResizableRectItem *tempRectItem = qgraphicsitem_cast<ResizableRectItem *>(item);
        if(tempRectItem) {
            rectItem = tempRectItem;
            break;
        }
    }

    QPointF rectItemCenter = rectItem->sceneBoundingRect().center();
    QPointF mouseClick = mouseEvent->scenePos();

    rectItem->moveBy(mouseClick.x()-rectItemCenter.x(), mouseClick.y()-rectItemCenter.y());
};
