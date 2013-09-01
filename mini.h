#ifndef MINI_H
#define MINI_H

#include <QGLWidget>

class Widget;

class Mini : public QGLWidget
{
    Q_OBJECT
public:
    explicit Mini(Widget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void calcScale();
    void changeFView(QPointF);

signals:
    
public slots:
    void reposit();

public:
    Widget *fa;
    float scale,mx,my;
    
};

#endif // MINI_H
