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
    status.totalCount++;
    makeStatusUpdate();
    QThreadPool::globalInstance()->start(optimizer);
}
void OptimizationQueue::itemFinished(int finishStatus)
{
    if(finishStatus != 0) status.errorCount++;
    status.completedCount++;
    makeStatusUpdate();
}
void OptimizationQueue::makeStatusUpdate()
{
    emit updateStatus(status);
}
