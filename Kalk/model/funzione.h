#ifndef FUNZIONE_H
#define FUNZIONE_H

#include "functionresult.h"
#include "aritmetica.h"
#include <vector>

class Funzione : public Aritmetica
{
public:
    Funzione(const std::string s);
    Funzione(const Funzione&);
    Funzione();

    Result* calculate();

    Funzione& operator =(const Funzione &);
    Funzione operator +(const Funzione&) const;
    Funzione operator -(const Funzione&) const;
    Funzione operator *(const Funzione&) const;
    Funzione operator /(const Funzione&) const;
    Funzione operator +(const char) const;
    Funzione operator +(const int) const;
    operator double() const;
    Funzione& operator --();
};

#endif // FUNZIONE_H
