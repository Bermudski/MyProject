#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
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
    filepath = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/vladimir", tr("File (*.txt)"));
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
        object[0] = obj["road1"].toArray();
        object[1] = obj["road2"].toArray();
        object[2] = obj["road3"].toArray();
        map();
        line(p1,v1,object);
    }

}
void MainWindow::map(){
    QJsonArray r1 = obj["road1"].toArray();
    QJsonArray r2 = obj["road2"].toArray();
    QJsonArray r3 = obj["road3"].toArray();

}

void MainWindow::line(QPainterPath &p, QVector<QPointF> &v, QJsonArray *r){
    double k = 3;
    for(int i = 0; i<3; i++){
        for(int j = 0; j < r[i].count(); j++){

            QJsonObject pointobj1 = r[i][j].toObject();
            QPointF point(pointobj1["x"].toDouble()*k, pointobj1["y"].toDouble()*k);
            v.append(point);
            if(j==0 ){
                p.moveTo(point);
            }else{
                p.lineTo(point);
            }
        }
        scene.addPath(p);
        scene.setV1(v);
        scene.setV2(v);
        scene.setV3(v);


    }
}


