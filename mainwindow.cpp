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

const char* convertStr(QString str){
    QByteArray bytes = str.toUtf8();
    const char* charstr;
    charstr = bytes.constData();
    return charstr;
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
        int size = obj.keys().size();
        QString road = "road";
        for (int i = 0; i<size;i++){
            std::string s = (road + QLocale().toString(i + 1)).toStdString();
            arr.push_back(obj[s.c_str()].toArray());
            qDebug() << obj[QString("road") + QChar(i + 1)];
        }

        line(p1,v1, arr, size);
    }

}

void MainWindow::line(QPainterPath &p, QVector<QPointF> &v, QVector<QJsonArray> r, int size){
    double k = 3;
    for(int i = 0; i<size; i++){

          for(int j = 0; j < r[i].count(); j++){

              QJsonArray ja = r[i];
              QJsonObject pointobj1 = ja[j].toObject();
              QPointF point(pointobj1["x"].toDouble()*k, pointobj1["y"].toDouble()*k);
                    v.append(point);
                    if(j==0 ){
                        p.moveTo(point);
                    }else{
                        p.lineTo(point);
                    }
                }


    }
        scene.addPath(p);
        scene.setV1(v);
        scene.setV2(v);
        scene.setV3(v);


}

