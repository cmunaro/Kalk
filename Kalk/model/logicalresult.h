#ifndef LOGICALRESULT_H
#define LOGICALRESULT_H

#include "result.h"
#include <math.h>
#include <vector>

class LogicalResult : public Result
{
private:
    std::vector<std::vector<bool>> matrix;
    std::vector<char> columns;

public:
    LogicalResult(const std::vector<std::vector<bool>>& matrix, const std::vector<char>& c);
    LogicalResult(const LogicalResult&);
    ~LogicalResult();
    std::vector<char> getColumnNames() const;
    std::vector<std::vector<bool>> getMatrix() const;
    void stampa() const;

    LogicalResult& operator =(const LogicalResult&);
    operator double() const;
};

#endif // LOGICALRESULT_H
