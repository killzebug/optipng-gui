#ifndef OPTIMIZATIONQUEUE_H
#define OPTIMIZATIONQUEUE_H

#include <QObject>
#include "optimizationStatus.h"

class OptimizationQueue : public QObject
{
    Q_OBJECT
public:
    explicit OptimizationQueue(QObject *parent = nullptr);
    void queue(const char* command);

signals:
    void updateStatus(optimizationStatus& status);
private slots:
    void itemFinished(int status);
private:
    void makeStatusUpdate();
    optimizationStatus status;
};

#endif // OPTIMIZATIONQUEUE_H
