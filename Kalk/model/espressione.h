#ifndef ESPRESSIONE_H
#define ESPRESSIONE_H

#include "result.h"
#include "eccezione.h"

class Espressione
{
protected:
    std::string text;
    Result* result;
    bool checkParentesi() const;    //Controlla il bilanciamento delle parentesi

    Espressione(const std::string);
    virtual ~Espressione();

public:
    Result* getResult() const;
    std::string getText() const;

    virtual Result* calculate() =0;
    virtual operator double() const =0;
};

#endif // ESPRESSIONE_H
