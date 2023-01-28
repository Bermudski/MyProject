#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QJsonObject>
#include"graphicscen.h"
#include<QGraphicsView>
#include<QJsonArray>


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onopenfile();

private:
    void map();
    void line(QPainterPath &p, QVector<QPointF> &v, QVector<QJsonArray> r, int size);
private:
    QString filepath;
    QJsonObject obj;
    GraphicScen scene;
    QPainterPath p1, p2, p3;
    QVector<QPointF> v1, v2, v3;
    QVector<QJsonArray> arr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
