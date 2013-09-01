#include "widget.h"
#include "mainwidget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGLFormat glf = QGLFormat::defaultFormat();
    glf.setSampleBuffers(true);
    glf.setSamples(4);
    QGLFormat::setDefaultFormat(glf);
    QFile file("://style.css");
    file.open(QIODevice::ReadOnly);
    a.setStyleSheet(file.readAll());
    MainWidget w;
    w.show();
    
    return a.exec();
}
