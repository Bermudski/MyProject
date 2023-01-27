#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QFileDialog>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QJsonArray>
#include<QGraphicsView>
#include<QPainterPath>
#include<QGraphicsPolygonItem>
#include<QFile>
#include<QPen>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionOpen_JSON_file, &QAction::triggered, this, &MainWindow::onopenfile);
    setCentralWidget(new QGraphicsView(&scene));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onopenfile()
{
    filepath = QFileDialog::getOpenFileName(this, tr("Open JSON"), "/home/vladimir", tr("JSON Files (*.json)"));
    QFile f(filepath);
    if (f.open(QIODevice::ReadOnly)){
        QByteArray ba = f.readAll();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(ba, &error);
        if (error.error != QJsonParseError::NoError){
            qDebug()<<error.errorString()<<" "<< error.offset;
        }
        obj = doc.object();
        qDebug()<<obj.keys();
        f.close();
        map();
    }

}
void MainWindow::map()
{
    QJsonArray r1 = obj["road1"].toArray();
    QJsonArray r2 = obj["road2"].toArray();
    QJsonArray r3 = obj["road3"].toArray();
    QPainterPath p1, p2, p3;
    QVector<QPointF> v1, v2, v3;

    double k = 3; //Увеличиваем график

    for(int i = 0; i<r1.count(); i++){
        QJsonObject pointobj1 = r1[i].toObject();
        QPointF point1(pointobj1["x"].toDouble()*k, pointobj1["y"].toDouble()*k);
        v1.append(point1);
        if(i==0 ){
            p1.moveTo(point1);
        }else{
            p1.lineTo(point1);
        }
    }
    for(int i=0; i<r2.count(); i++){
        QJsonObject pointobj2 = r2[i].toObject();
        QPointF point2(pointobj2["x"].toDouble()*k, pointobj2["y"].toDouble()*k);
        v2.append(point2);
        if(i==0){
            p2.moveTo(point2);
        }else{
            p2.lineTo(point2);
        }
    }
    for(int i=0; i<r3.count(); i++){
        QJsonObject pointobj3 = r3[i].toObject();
        QPointF point3(pointobj3["x"].toDouble()*k, pointobj3["y"].toDouble()*k);
        v3.append(point3);
        if(i==0){
            p3.moveTo(point3);

        }else{
            p3.lineTo(point3);
        }
    }
    scene.addPath(p1);
    scene.setV1(v1);
    scene.addPath(p2);
    scene.setV2(v2);
    scene.addPath(p3);
    scene.setV3(v3);

}

