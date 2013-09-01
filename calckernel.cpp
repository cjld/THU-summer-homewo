#include "calckernel.h"
#include <fly.h>
#include <vector>
#include <QDebug>

using std::vector;

int kn,*kx,*ky;
vector<int> klx,kly;

CalcKernel::CalcKernel(QObject *parent) :
    QThread(parent)
{
}

void CalcKernel::run() {
    GetTree getTree;
    getTree.work(kn,kx,ky);
    getTree.tree.dp(klx,kly);
}
