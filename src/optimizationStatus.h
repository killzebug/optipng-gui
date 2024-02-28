#ifndef OPTIMIZATIONSTATUS_H
#define OPTIMIZATIONSTATUS_H
#include <sys/types.h>
struct optimizationStatus
{
    uint completedCount{};
    uint totalCount{};
    uint errorCount{};
};
#endif // OPTIMIZATIONSTATUS_H
