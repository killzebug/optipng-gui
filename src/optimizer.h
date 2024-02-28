#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <QObject>
#include <QThreadPool>

class Optimizer : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Optimizer(QObject *parent = nullptr);
    void setCommand(const char* newCommand);
    // QRunnable interface
    void run();
signals:
    void finished(int status);
private:
    const char* command;


};

#endif // OPTIMIZER_H
