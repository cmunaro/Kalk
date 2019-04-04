#ifndef ECCEZIONE_H
#define ECCEZIONE_H

#include <iostream>

class Eccezione
{
private:
    std::string motivo;
public:
    Eccezione(const std::string);
    ~Eccezione() = default;

    std::string getError() const;
};

#endif // ECCEZIONE_H
