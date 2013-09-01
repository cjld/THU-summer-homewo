#include "mini.h"
#include <widget.h>
#include <QMouseEvent>
#include <QDebug>

Mini::Mini(Widget *parent) :
    QGLWidget(parent) {
    fa=parent;
    reposit();
}

void Mini::reposit() {
    int ww=150,hh=150;
    setGeometry(fa->width()-ww,fa->height()-hh,ww,hh);
}

void Mini::initializeGL() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.2, 0.2, 0.2, 1);

    glEnable(GL_MULTISAMPLE);
    GLint bufs;
    GLint samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);
    qDebug("Have %d buffers and %d samples", bufs, samples);
}

void Mini::resizeGL(int width, int height) {
    if (!height) height=1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
}

void Mini::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    calcScale();

    glColor3f(1,1,1);
    glLineWidth(0.4);
    glBegin(GL_LINES); {
        for (int i=0;i<(int)fa->lx.size();i++) if ((i&1)==0) {
            glVertex2f(fa->lx[i],fa->ly[i]);
            glVertex2f(fa->lx[i+1],fa->ly[i+1]);
        }
    } glEnd();

    glColor3f(1,1,0);
    glPointSize(2);
    glBegin(GL_POINTS); {
        for (auto p : fa->point)
            glVertex2f(p.x(), p.y());
    } glEnd();

    glColor3f(1,0,0);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP); {
        QPointF p1=fa->translate(QPoint(0,0));
        QPointF p2=fa->translate(QPoint(fa->width(),fa->height()));
        glVertex2f(p1.x(),p1.y());
        glVertex2f(p1.x(),p2.y());
        glVertex2f(p2.x(),p2.y());
        glVertex2f(p2.x(),p1.y());
    } glEnd();

    glLoadIdentity();
    glColor3f(0,0,0);
    glLineWidth(5);
    glBegin(GL_LINE_LOOP); {
        glVertex2f(0,0);
        glVertex2f(this->width(),0);
        glVertex2f(this->width(),this->height());
        glVertex2f(0,this->height());
    } glEnd();
}

void Mini::mousePressEvent(QMouseEvent *e) {
    changeFView(e->pos());
}

void Mini::mouseMoveEvent(QMouseEvent *e) {
    changeFView(e->pos());
}

void Mini::changeFView(QPointF p) {
    p=p/scale+QPointF(mx,my);
    p-=fa->translateV(QPoint(fa->width()/2,fa->height()/2));
    fa->no=-p;
    qDebug()<<p<<scale;
    fa->updateAll();
}

void Mini::calcScale() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int xl=0,yl=0,xr=1,yr=1;
    for (auto p : fa->point) {
        xl=min(xl,p.x());
        xr=max(xr,p.x());
        yl=min(yl,p.y());
        yr=max(yr,p.y());
    }
    float len=max(xr-xl,yr-yl)*0.6 + 1;
    mx=(xl+xr)/2-len,my=(yl+yr)/2-len;
    scale=this->width()/(len*2.);
    glScalef(scale,scale,scale);
    glTranslatef(-mx,-my,0);
}
