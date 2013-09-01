#ifndef ASKWIDGET_H
#define ASKWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class AskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AskWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
};

#endif // ASKWIDGET_H
