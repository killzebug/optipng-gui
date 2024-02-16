#include "optimizationqueue.h"
#include "optimizer.h"

OptimizationQueue::OptimizationQueue(QObject *parent)
    : QObject{parent}
{

}
void OptimizationQueue::queue(const char *command)
{
    Optimizer* optimizer = new Optimizer;
    optimizer->setAutoDelete(true);
    optimizer->setCommand(command);
    connect(optimizer,&Optimizer::finished,this,&OptimizationQueue::itemFinished);
    ++totalCount;
    makeStatusUpdate();
    QThreadPool::globalInstance()->start(optimizer);
}
void OptimizationQueue::itemFinished(int status)
{
    if(status != 0) ++errorCount;
    ++completedCount;
    makeStatusUpdate();
}
void OptimizationQueue::makeStatusUpdate()
{
    uint output[] = {completedCount,totalCount,errorCount};
    emit updateStatus(output);
}
