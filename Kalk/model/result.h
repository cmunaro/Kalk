#ifndef RESULT_H
#define RESULT_H

#include <iostream>

class Result
{
public:
    virtual ~Result() =default;
    virtual void stampa() const =0;
};

#endif // RESULT_H
