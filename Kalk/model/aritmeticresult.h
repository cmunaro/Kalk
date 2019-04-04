#ifndef EXPRESSIONRESULT_H
#define EXPRESSIONRESULT_H

#include "result.h"

class AritmeticResult : public Result
{
private:
    double ris;
public:
    AritmeticResult(const double);
    AritmeticResult(const AritmeticResult&);
    void stampa() const;
    double getValue() const;

    AritmeticResult& operator =(const AritmeticResult&);
    operator double() const;
};

#endif // EXPRESSIONRESULT_H
