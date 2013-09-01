#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QLabel>
#include <vector>

using std::vector;

class ToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit ToolBar(QWidget *parent = 0);
    void addButton(QString);
    void mousePressEvent(QMouseEvent *);
    int getWho(QPoint);
    void pressTool(int);
    void recoverAll();
    
signals:
    void press(QString);

public slots:

private:
    vector<QLabel*> labels;
};

#endif // TOOLBAR_H
