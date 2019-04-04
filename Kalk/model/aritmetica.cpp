#include "aritmetica.h"

Aritmetica::Aritmetica(const std::string s) : Espressione(s) {}

Aritmetica::Aritmetica(const Aritmetica& a) : Espressione(a.text)
{
    if(a.result)
        result = new AritmeticResult(*dynamic_cast<AritmeticResult *>(a.result));
    else
        result = nullptr;
}

Aritmetica::Aritmetica() : Aritmetica("") {}

Aritmetica& Aritmetica::operator =(const Aritmetica& a)
{
  if(this != &a) {
    if (result)
        delete result;
    if (a.result)
        result = new AritmeticResult(*dynamic_cast<AritmeticResult *>(a.result));
    text = a.text;
  }
  return *this;
}

Aritmetica Aritmetica::operator +(const Aritmetica& a) const
{
    Aritmetica neo(text + '+' + a.text);
    return neo;
}

Aritmetica Aritmetica::operator -(const Aritmetica& a) const
{
    Aritmetica neo("(" + text + ")-(" + a.text + ')');
    return neo;
}

Aritmetica Aritmetica::operator *(const Aritmetica& a) const
{
    Aritmetica neo("(" + text + ")*(" + a.text + ')');
    return neo;
}

Aritmetica Aritmetica::operator /(const Aritmetica& a) const
{
    Aritmetica neo("(" + text + ")/(" + a.text + ')');
    return neo;
}

Aritmetica Aritmetica::operator +(const char c) const
{
    Aritmetica neo(text + c);
    return neo;
}

Aritmetica Aritmetica::operator +(const int i) const
{
    std::string s = "";
    if (text.size() > 0 && text[text.size() - 1] != '+' && text[text.size() - 1] != '-' &&
            text[text.size() - 1] != '*' && text[text.size() - 1] != '/')
        s = '+';
    Aritmetica neo(text + s + std::to_string(i));
    return neo;
}

Aritmetica::operator double() const
{
    if(result) return dynamic_cast<AritmeticResult*>(result)->operator double();
    return 0;
}

Aritmetica& Aritmetica::operator --()
{
    if (text.size() > 0) {
        text = text.substr(0, text.size() - 1);
        if(result) {
            delete result;
            result = nullptr;
        }
    }
    return *this;
}

double Aritmetica::number()
{
    double result = static_cast<double>(text[i++] - '0');
    while (i < text.length() && text[i] >= '0' && text[i] <= '9')
        result = 10 * result + text[i++] - '0';
    return result;
}

double Aritmetica::factor()
{
    if (text[i] >= '0' && text[i] <= '9')
        return number();
    else if (text[i] == '(') {
        i++; // '('
        double result = sum();
        i++; // ')'
        return result;
    } else if (text[i] == '-') {
        i++;
        return -factor();
    }
    throw Eccezione("Espressione non valida");
}

double Aritmetica::priority()
{
    double result = factor();
    while (i < text.length() && (text[i] == '*' || text[i] == '/'))
        if (text[i++] == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

double Aritmetica::sum()
{
    double result = priority();
    while (i < text.length() && (text[i] == '+' || text[i] == '-'))
        if (text[i++] == '+')
            result += priority();
        else
            result -= priority();
    return result;
}

double Aritmetica::evaluate()
{
    for(unsigned int i = 0; i < text.length(); ++i)
        if (!isSymbol(text[i]) && !isNumber(text[i]))
            throw Eccezione("Espressione non valida");

    i = 0;
    return sum();
}

bool Aritmetica::isNumber(const char c) const
{
    return c >= '0' && c <= '9';
}

bool Aritmetica::isSymbol(const char c) const
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

Result* Aritmetica::calculate()
{
    if(!checkParentesi())
        throw Eccezione("Espressione non valida");
    for(unsigned int i = 0; i < text.length() - 1; ++i)
        if(text[i] == ')' && isNumber(text[i+1]))
            throw Eccezione("Espressione non valida");
    double evaluated = evaluate();
    result = new AritmeticResult(evaluated);
    return result;
}
