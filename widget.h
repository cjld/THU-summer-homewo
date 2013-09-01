#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <vector>
#include <map>
#include <mini.h>
#include <toolbar.h>
#include <calckernel.h>
#include <askwidget.h>

using namespace std;

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );

    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);
    void resizeEvent(QResizeEvent *);
    void addPoint(QPoint);
    void addRandPoint(int);
    void moveViewPort(QPoint);
    void selectArea(QPoint,QPoint);
    void moveArea(QPoint);
    void deleteArea();
    QPointF translate(QPoint);
    QPointF translateV(QPoint);
    void scaleViewPort(QPoint,double);
    void calc();
    void updateAll();
    void openPointFile();
    void printAns();

public slots:
    void toolAction(QString);
    void calcComplete();
    void askRandPoint();

public:
    Ui::Widget *ui;
    vector<QPoint> point;
    vector<bool> selectPoint;
    int selectSize=0;
    map<int,int> keymap;
    QPoint mpos,prepos;
    QPointF no,s1,s2;
    double scale=1;
    vector<int> lx,ly;
    Mini *mini;
    QString statu;
    CalcKernel *kernel;
    AskWidget *askWidget;
    int dataChg=0;
};

#endif // WIDGET_H
