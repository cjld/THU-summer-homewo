#include "widget.h"
#include "ui_widget.h"
#include <GL/glu.h>
#include <QMouseEvent>
#include <QDebug>
#include <cmath>
#include <fly.h>
#include <askwidget.h>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

extern int kn,*kx,*ky;
extern vector<int> klx,kly;

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mini=new Mini(this);
    kernel=new CalcKernel(this);
    askWidget=new AskWidget();
    connect(kernel,SIGNAL(finished()),this,SLOT(calcComplete()));
    connect(askWidget->pushButton,SIGNAL(clicked()),this,SLOT(askRandPoint()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateAll() {
    updateGL();
    mini->updateGL();
}

void Widget::initializeGL() {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1, 0.1, 0.1, 0.0);

    glEnable(GL_MULTISAMPLE);
    GLint bufs;
    GLint samples;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &bufs);
    glGetIntegerv(GL_SAMPLES, &samples);
    qDebug("Have %d buffers and %d samples", bufs, samples);
    //抗锯齿
}

void Widget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(scale,scale,scale);
    glTranslatef(no.x(),no.y(),0);

    glColor3f(1,1,1);
    glBegin(GL_LINES); {
        for (int i=0;i<(int)lx.size();i++) if ((i&1)==0) {
            glVertex2f(lx[i],ly[i]);
            glVertex2f(lx[i+1],ly[i+1]);
        }
    } glEnd();

    glColor3f(1,1,0);
    glPointSize(5);
    glBegin(GL_POINTS); {
        int i=0;
        for (auto p : point) {
            if (selectPoint[i]) glColor3f(1,0,0);
            else glColor3f(1,1,0);
            glVertex2f(p.x(), p.y());
            i++;
        }
    } glEnd();

    if (selectSize) {
        glColor3f(0,1,1);
        glLineWidth(1);
        glBegin(GL_LINE_LOOP); {
            glVertex2f(s1.x(),s1.y());
            glVertex2f(s1.x(),s2.y());
            glVertex2f(s2.x(),s2.y());
            glVertex2f(s2.x(),s1.y());
        } glEnd();
    }
}

void Widget::resizeGL(int width, int height) {
    if (!height) height=1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
}

void Widget::resizeEvent(QResizeEvent *e) {
    QGLWidget::resizeEvent(e);
    mini->reposit();
    mini->updateGL();
}

void Widget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_R) addRandPoint(100);
}

void Widget::mousePressEvent(QMouseEvent *e) {
    prepos=e->pos();
    mpos=e->pos();
    keymap[e->button()]=1;
    if (e->button() == Qt::RightButton) {
        addPoint(e->pos());
        calc();
        updateAll();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *e) {
    keymap[e->button()]=0;
}

void Widget::wheelEvent(QWheelEvent *e) {
    scaleViewPort(e->pos(),e->angleDelta().y()/1200.);
}

void Widget::mouseMoveEvent(QMouseEvent *e) {
    if (keymap[Qt::LeftButton] && statu=="移动")
        moveViewPort(e->pos()-mpos);
    if (keymap[Qt::LeftButton] && statu=="选定")
        selectArea(prepos,e->pos());
    if (keymap[Qt::LeftButton] && statu=="拖动")
        moveArea(e->pos());
    mpos=e->pos();
}

void Widget::moveArea(QPoint p) {
    QPointF mv=translateV(p-mpos);
    s1+=mv,s2+=mv;
    int i=0;
    for (auto &x : point) {
        if (selectPoint[i]) x+=mv.toPoint();
        i++;
    }
    calc();
    updateAll();
}

void Widget::selectArea(QPoint l, QPoint r) {
    s1=translate(l);
    s2=translate(r);
    l=translate(l).toPoint();
    r=translate(r).toPoint();
    int xl=min(l.x(),r.x()),xr=max(l.x(),r.x());
    int yl=min(l.y(),r.y()),yr=max(l.y(),r.y());
    selectSize=0;
    for (size_t i=0; i<point.size(); i++) {
        selectPoint[i]=(xl<point[i].x() && xr>point[i].x() &&
                        yl<point[i].y() && yr>point[i].y() );
        selectSize+=selectPoint[i];
    }
    updateAll();
}

void Widget::deleteArea() {
    if (selectSize==0) return;
    vector<QPoint> newvector;
    int i=0;
    for (auto x : point) {
        if (!selectPoint[i]) newvector.push_back(x);
        selectPoint[i]=0;
        i++;
    }
    point=newvector;
    selectPoint.resize(point.size());
    selectSize=0;
    calc();
    updateAll();
}

void Widget::toolAction(QString s) {
    statu=s;
    if (s=="退出") exit(0);
    if (s=="删除") deleteArea();
    if (s=="随机撒点...") askWidget->show();
    if (s=="打开...") openPointFile();
    if (s=="导出方案...") printAns();
}

QPointF Widget::translate(QPoint p) {
    QPointF pp=p;
    return pp/scale-no;
}

QPointF Widget::translateV(QPoint p) {
    QPointF pp=p;
    return pp/scale;
}

void Widget::addPoint(QPoint p) {
    point.push_back(translate(p).toPoint());
    selectPoint.push_back(0);
}

void Widget::addRandPoint(int n) {
    for (int i=1;i<=n;i++)
        addPoint(QPoint(rand()%(width()+1), rand()%(height()+1)));
    calc();
    updateAll();
}

void Widget::askRandPoint() {
    addRandPoint(askWidget->lineEdit->text().toInt());
}

void Widget::scaleViewPort(QPoint p, double s) {
    if (s<0 && scale<1e-4) return;
    QPointF a=p;
    s=exp(s);
    no=a/(s*scale)-a/scale+no;
    scale*=s;
    updateAll();
}

void Widget::moveViewPort(QPoint p) {
    no+=translateV(p);
    updateAll();
}
/*
void Widget::calc() {
    lx.clear();ly.clear();
    klx.clear();kly.clear();
    if (point.size()<2) return;
    ::x=new int[point.size()+1];
    ::y=new int[point.size()+1];
    for (int i=0;i<(int)point.size();i++)
        ::x[i+1]=point[i].x(),::y[i+1]=point[i].y();
    GetTree getTree;
    getTree.work(point.size(),::x,::y);
    getTree.tree.dp(lx,ly);
    delete[] ::x;
    delete[] ::y;
}
*/
void Widget::calc() {
    dataChg=1;
    if (point.size()<2) {
        lx.clear();ly.clear();
        return;
    }
    if (kernel->isRunning()) return;
    klx.clear();kly.clear();
    kx=new int[point.size()+1];
    ky=new int[point.size()+1];
    kn=this->point.size();
    for (int i=0;i<(int)point.size();i++)
        kx[i+1]=point[i].x(),ky[i+1]=point[i].y();
    dataChg=0;
    kernel->start();
}

void Widget::calcComplete() {
    delete[] kx;
    delete[] ky;
    lx.swap(klx);ly.swap(kly);
    updateAll();
    if (dataChg==1) calc();
}

void Widget::openPointFile() {
    QString name=QFileDialog::getOpenFileName(0,"打开文件...");
    if (name.isEmpty()) return;
    QFile file(name);
    file.open(QIODevice::ReadOnly);
    QTextStream qin(&file);
    int size=0;
    qin>>size;
    point.clear();
    for (int i=0;i<size;i++) {
        int x,y;
        qin>>x>>y;
        point.push_back(QPoint(x,y));
        selectPoint.push_back(0);
    }
    selectSize=0;
    calc();
}

void Widget::printAns() {
    QString name=QFileDialog::getSaveFileName(0,"打开文件...");
    if (name.isEmpty()) return;
    QFile file(name);
    file.open(QIODevice::WriteOnly);
    QTextStream qout(&file);
    qout<<lx.size()<<endl;
    for (size_t i=0; i<lx.size(); i++) if (i%2==0)
        qout<<lx[i]<<' '<<ly[i]<<' '<<lx[i+1]<<ly[i+1]<<endl;
}
