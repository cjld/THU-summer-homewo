#include "toolbar.h"
#include <QMouseEvent>
#include <QFile>

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent)
{
    setGeometry(0,0,100,300);
    addButton("移动");
    addButton("选定");
    addButton("拖动");
    addButton("删除");
    addButton("打开...");
    addButton("导出方案...");
    addButton("随机撒点...");
    addButton("退出");
}

void ToolBar::mousePressEvent(QMouseEvent *e) {
    int w=getWho(e->pos());
    if (w==-1) return;
    pressTool(w);
}

int ToolBar::getWho(QPoint p) {
    for (size_t i=0; i<labels.size(); i++) {
        QLabel *label=labels[i];
        if (p.x()>label->pos().x() && p.y()>label->pos().y() &&
            p.x() < label->pos().x()+label->width() && p.y() < label->pos().y()+label->height())
            return i;
    }
    return -1;
}

void ToolBar::recoverAll() {
    QFile file("://style.css");
    file.open(QIODevice::ReadOnly);
    for (auto x : labels)
        x->setStyleSheet(file.readAll());
}

void ToolBar::pressTool(int x) {
    recoverAll();
    labels[x]->setStyleSheet("background-color : rbg(100,100,100);");
    emit press(labels[x]->text());
}

void ToolBar::addButton(QString s) {
    QLabel *label=new QLabel(this);
    label->setText(s);
    int n=labels.size();
    int ww=this->width()-20,hh=50;
    label->setGeometry(10,10+n*hh,ww,hh-5);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    labels.push_back(label);
    this->setGeometry(this->pos().x(),pos().y(),width(),(n+1)*hh+20);
}
