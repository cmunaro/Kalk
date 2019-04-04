#ifndef FUNCTIONRESULT_H
#define FUNCTIONRESULT_H

#include "result.h"
#include <vector>

class FunctionResult : public Result
{
private:
    std::vector<std::pair<double, double>> points;

public:
    FunctionResult(const std::vector<std::pair<double, double>> v);
    FunctionResult(const FunctionResult& f);
    std::vector<std::pair<double, double>> getPoints() const;
    void stampa() const;

    FunctionResult& operator =(const FunctionResult&);
    operator double() const;
};

#endif // FUNCTIONRESULT_H
