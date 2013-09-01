#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <widget.h>
#include <toolbar.h>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);
    void keyPressEvent(QKeyEvent *);
    
signals:
    
public slots:
    
private:
    Widget *glw;
    ToolBar *toolbar;
};

#endif // MAINWIDGET_H
