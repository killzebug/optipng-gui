#ifndef OPTIMIZATIONQUEUE_H
#define OPTIMIZATIONQUEUE_H

#include <QObject>

class OptimizationQueue : public QObject
{
    Q_OBJECT
public:
    explicit OptimizationQueue(QObject *parent = nullptr);
    void queue(const char* command);

signals:
    void updateStatus(uint* status);
private slots:
    void itemFinished(int status);
private:
    void makeStatusUpdate();
    uint totalCount{};
    uint completedCount{};
    uint errorCount{};
};

#endif // OPTIMIZATIONQUEUE_H
