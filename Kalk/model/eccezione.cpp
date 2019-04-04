#include "eccezione.h"

Eccezione::Eccezione(const std::string s) : motivo(s) {}

std::string Eccezione::getError() const
{
    return motivo;
}
