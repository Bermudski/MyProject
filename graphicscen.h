#ifndef GRAPHICSCEN_H
#define GRAPHICSCEN_H

#include <QGraphicsScene>
#include<QPainterPath>
#include<QVector>
#include<math.h>

class GraphicScen : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GraphicScen(QObject *parent = nullptr);

    void setV1(const QVector<QPointF> &newV1);

    void setV2(const QVector<QPointF> &newV2);

    void setV3(const QVector<QPointF> &newV3);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void addline(QPointF& p);

    void getmin(QVector<QPointF> &v, QPointF &p);

private:
    int counter = 0;
    QPointF p1; //Начальная точка
    QPointF p2; //Конечная точка
    QVector<QPointF> v1, v2, v3; //Обозначения ломаных
    QPointF pmin; //Точка на ломаной
    double mindistanse; //Точка с минимальной дистанцией до ломаной
};


#endif // GRAPHICSCEN_H
