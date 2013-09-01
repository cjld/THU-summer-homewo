#ifndef CALCKERNEL_H
#define CALCKERNEL_H

#include <QThread>

class CalcKernel : public QThread
{
    Q_OBJECT
public:
    explicit CalcKernel(QObject *parent = 0);
    void run();
    
signals:
    
public slots:
    
};

#endif // CALCKERNEL_H
