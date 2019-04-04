#ifndef LOGICA_H
#define LOGICA_H

#include "logicalresult.h"
#include "espressione.h"
#include <vector>
#include <algorithm>
#include <math.h>

class Logica : public Espressione
{
private:
    std::vector<std::pair<char, bool>>* vars = new std::vector<std::pair<char, bool> >(); //Vettore variabile-stato_tentativo

    bool isSymbol(const char) const;
    bool evaluate(std::string);

public:
    Logica(const std::string);
    Logica(const Logica&);
    Logica();

    Result* calculate();

    Logica& operator =(const Logica&);
    Logica operator +(const Logica&) const;
    Logica operator -(const Logica&) const;
    Logica operator +(const char) const;
    Logica operator +(const int) const;
    operator double() const;
    Logica& operator --();
};

#endif // LOGICA_H
