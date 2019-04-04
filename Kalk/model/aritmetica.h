#ifndef ARITMETICA_H
#define ARITMETICA_H

#include "espressione.h"
#include "eccezione.h"
#include "aritmeticresult.h"

class Aritmetica : public Espressione
{
private:
    size_t i;

    bool isSymbol(const char) const;
    double number();    //String to number
    double factor();    //Ritorna il risultato di una sottoespressione
    double priority();  //Ritorna il risultato di una moltplicazione o divisione
    double sum();       //Ritorna il risultato di una somma o sotrazzione

protected:
    double evaluate();
    bool isNumber(const char) const;

public:
    Aritmetica(const std::string);
    Aritmetica(const Aritmetica&);
    Aritmetica();

    Result* calculate();

    Aritmetica& operator =(const Aritmetica&);
    Aritmetica operator +(const Aritmetica&) const;
    Aritmetica operator -(const Aritmetica&) const;
    Aritmetica operator *(const Aritmetica&) const;
    Aritmetica operator /(const Aritmetica&) const;
    Aritmetica operator +(const char) const;
    Aritmetica operator +(const int) const;
    Aritmetica& operator --();
    operator double() const;
};

#endif // ARITMETICA_H
