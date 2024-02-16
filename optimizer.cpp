#include "optimizer.h"
#include <QThread>
#include <QDebug>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
Optimizer::Optimizer(QObject *parent)
    : QObject{parent}
{

}
void Optimizer::setCommand(const char* newCommand)
{
    //command = std::_strdup(newCommand);

    int commandSize = strlen(newCommand) + 1; //strlen doesn't count nullterm
    command = std::strcpy(new char[commandSize],newCommand);
}

void Optimizer::run()
{
    int status = std::system(command);
    delete command;
    emit finished(status);
}
