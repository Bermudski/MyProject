#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QJsonObject>
#include"graphicscen.h"
#include<QGraphicsView>


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
private:
    QString filepath;
    QJsonObject obj;
    GraphicScen scene;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
