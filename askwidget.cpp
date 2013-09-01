#include "askwidget.h"

AskWidget::AskWidget(QWidget *parent) :
    QWidget(parent)
{
    lineEdit=new QLineEdit(this);
    pushButton=new QPushButton(this);
    this->setGeometry(300,300,300,40);
    lineEdit->setGeometry(5,5,200,30);
    pushButton->setGeometry(205,5,90,30);
    pushButton->setText("确定");
    setWindowTitle("输入数据");
    connect(pushButton,SIGNAL(clicked()),this,SLOT(close()));
}
