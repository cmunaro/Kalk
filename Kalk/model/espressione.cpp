#include "espressione.h"
#include "aritmeticresult.h"

Espressione::Espressione(const std::string s) : text(s), result(nullptr) {}

Espressione::~Espressione() {
    delete result;
}

Result* Espressione::getResult() const
{
    if(result)
        return result;
    return nullptr;
}

std::string Espressione::getText() const
{
    return std::string(text);
}

bool Espressione::checkParentesi() const
{
    int check = 0;
    for(unsigned int i = 0; i < text.length(); ++i)
        if(text[i] == '(')
            ++check;
        else if(text[i] == ')' && --check < 0)
            return 0;
    if(check != 0)
        return false;
    for(unsigned int i = 0; i < text.length() - 1; ++i)
        if (text[i] == '(' && text[i+1] == ')'  )
            return false;
    return true;
}
