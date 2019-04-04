#include "funzione.h"
#include "eccezione.h"

Funzione::Funzione(const std::string s) : Aritmetica(s) {}

Funzione::Funzione(const Funzione& f) : Aritmetica(f.text)
{
    if (result)
        result = new FunctionResult(*dynamic_cast<FunctionResult *>(f.result));
    else
        result = nullptr;
}

Funzione::Funzione() : Funzione("") {}

Funzione& Funzione::operator =(const Funzione& f)
{
    if (this != &f) {
        if(result)
            delete result;
        if (f.result) result = new FunctionResult(*dynamic_cast<FunctionResult *>(f.result));
    }
    return *this;
}

Funzione Funzione::operator +(const Funzione& a) const
{
    Funzione neo(text + '+' + a.text);
    return neo;
}

Funzione Funzione::operator -(const Funzione& a) const
{
    Funzione neo("(" + text + ")-(" + a.text + ')');
    return neo;
}

Funzione Funzione::operator *(const Funzione& a) const
{
    Funzione neo("(" + text + ")*(" + a.text + ')');
    return neo;
}

Funzione Funzione::operator /(const Funzione& a) const
{
    Funzione neo("(" + text + ")/(" + a.text + ')');
    return neo;
}

Funzione Funzione::operator +(const char c) const
{
    Funzione neo(text + c);
    return neo;
}

Funzione Funzione::operator +(const int i) const
{
    std::string s = "";
    if (text.size() > 0 && text[text.size() - 1] != '+' && text[text.size() - 1] != '-'
            && text[text.size() - 1] != '*' && text[text.size() - 1] != '/')
        s = '+';
    Funzione neo(text + s + std::to_string(i));
    return neo;
}

Funzione& Funzione::operator --()
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


Funzione::operator double() const
{
    if(result)
        return dynamic_cast<FunctionResult*>(result)->operator double();
    return 0;
}

Result* Funzione::calculate()
{
    if(text.length() < 1)
        throw Eccezione("Espressione non valida");
    if(!checkParentesi())
        throw Eccezione("Espressione non valida");
    for(unsigned int i = 0; i < text.length() - 1; ++i)
        if((text[i] == ')' && isNumber(text[i+1])) || (isNumber(text[i]) && text[i+1] == 'x') || (isNumber(text[i+1]) && text[i] == 'x'))
            throw Eccezione("Espressione non valida");

    std::string original = text;
    std::vector<std::pair<double, double>> points;

    for(int i = -500; i < 501; i++) {
        std::pair<double, double> point;
        point.first = i;
        while(text.find('x') != std::string::npos && text[text.find('x')] == 'x')
            text.replace(text.find('x'), 1, std::to_string(i));
        try {
            point.second = Aritmetica::evaluate();
        } catch (Eccezione e) {
            text = original;    //Ripristina il testo della funzione
            throw e;            //E continua l'eccezzione
        }
        points.push_back(point);
        text = original;
    }

    result = new FunctionResult(points);
    return result;
}
