#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    glw=new Widget(this);
    toolbar=new ToolBar(this);
    connect(toolbar,SIGNAL(press(QString)),glw,SLOT(toolAction(QString)));
    toolbar->pressTool(0);
    //this->setWindowFlags(Qt::FramelessWindowHint);
}

void MainWidget::resizeEvent(QResizeEvent *e) {
    QWidget::resizeEvent(e);
    glw->setGeometry(0,0,width(),height());
}

void MainWidget::keyPressEvent(QKeyEvent *e) {
    glw->keyPressEvent(e);
}
