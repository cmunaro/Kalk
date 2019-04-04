#include "aritmeticresult.h"

AritmeticResult::AritmeticResult(const double ris) : Result(), ris(ris) {}

AritmeticResult::AritmeticResult(const AritmeticResult& e) : ris(e.ris) {}

AritmeticResult& AritmeticResult::operator =(const AritmeticResult& e)
{
    if(this != &e){
        ris = e.ris;
    }
    return *this;
}

AritmeticResult::operator double() const
{
    return ris;
}

double AritmeticResult::getValue() const
{
    return ris;
}

void AritmeticResult::stampa() const
{
    std::cout << "Ris: " << ris << std::endl;
}
