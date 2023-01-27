#include "graphicscen.h"
#include<QDebug>
#include<QGraphicsSceneMouseEvent>
#include<QPointF>
#include<QRectF>
#include<QPen>
#include<QColor>
#include<math.h>
#include<QGraphicsScene>

GraphicScen::GraphicScen(QObject *parent) //
    : QGraphicsScene{parent}
    , counter(0)
{

}

void GraphicScen::mousePressEvent(QGraphicsSceneMouseEvent *event)
//Начальная точка маршрута
{
    qDebug()<<event->scenePos() << " " << event->screenPos() << " " << event->lastPos();
    qDebug()<< counter;
    QPointF pos = event->scenePos();
    if(counter == 0){
        p1.setX(pos.x());
        p1.setY(pos.y());
        QRectF r(pos.x()-1, pos.y()-1, 3, 3);
        addEllipse(r, QPen(QColor(0,255,0)));
        counter++;

        addline(p1);

        //Конечная точка
    }else if(counter==1){
        p2.setX(pos.x());
        p2.setY(pos.y());
        QRectF r(pos.x()-1, pos.y()-1, 3, 3);
        addEllipse(r, QPen(QColor(255,0,0)));
        counter++;

        addline(p2);

    }
}

void GraphicScen::addline(QPointF &p)
{
    // добавить отрезок от точки до ближайшей ломаной
    //посчитать растояние до ломаной и выбрать минимальное
    //Вызываем функции ломаных
    mindistanse = 2000;
    getmin(v1,p);
    getmin(v2,p);
    getmin(v3,p);
    addLine(p.x(), p.y(), pmin.x(), pmin.y(), QPen(Qt::darkRed));
}
//Высчитываем минимальное растояние до ломаных
void GraphicScen::getmin(QVector<QPointF> &v, QPointF &p){
    for(int i=0; i<v.size(); i++){
        double dx = p.x()-v[i].x();
        double dy = p.y()-v[i].y();
        double distanse =sqrt(dx*dx+dy*dy);
        if(distanse<mindistanse)
        {
            pmin=v[i];
            mindistanse=distanse;
        }
    }
}



void GraphicScen::setV3(const QVector<QPointF> &newV3)
{
    v3 = newV3;
}

void GraphicScen::setV2(const QVector<QPointF> &newV2)
{
    v2 = newV2;
}

void GraphicScen::setV1(const QVector<QPointF> &newV1)
{
    v1 = newV1;
}





