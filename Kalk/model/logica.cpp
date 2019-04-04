#include "logica.h"

Logica::Logica(const std::string s) : Espressione(s) {}

Logica::Logica(const Logica & l) : Espressione(l.text)
{
    if (l.result)
        result = new LogicalResult(*dynamic_cast<LogicalResult *>(l.result));
    else
        result = nullptr;
}

Logica::Logica() : Logica("") {}

Logica& Logica::operator =(const Logica& l)
{
    if (this != &l) {
        text = l.text;
        delete result;
        if (l.result) result = new LogicalResult(*dynamic_cast<LogicalResult *>(l.result));
    }
    return *this;
}


Logica Logica::operator +(const Logica& a) const
{
    Logica neo(text + '+' + a.text);
    return neo;
}

Logica Logica::operator -(const Logica& a) const
{
    Logica neo("(" + text + ")&(" + a.text + ')');
    return neo;
}

Logica Logica::operator +(const char c) const
{
    Logica neo(text + c);
    return neo;
}

Logica Logica::operator +(const int i) const
{
    char r = i == 0 ? 0 : 1;
    std::string s = "";
    if (text.size() > 0 && text[text.size() - 1] != '|' && text[text.size() - 1] != '&' && text[text.size() - 1] != '!')
        s = '|';
    Logica neo(text + s + std::to_string(r));
    return neo;
}

Logica& Logica::operator --()
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

Logica::operator double() const
{
    if (result)
        return dynamic_cast<LogicalResult*>(result)->operator double();
    return 0;
}


bool Logica::isSymbol(const char c) const
{
    return c == '|' || c == '&' || c == '!' || c == '(' || c == ')';
}

bool Logica::evaluate(std::string s)
{
    unsigned int i = 0, indexParentesi = 0;
    bool op1 = false, op2 = false;

    while(s.length() != 1) {
        if(i >= s.length())
           i = 0;
        switch(s[i]) {
            case '(':
                indexParentesi = i;
                if(!isSymbol(s[i+1]) && s[i+2] == ')') {
                    if(isdigit(s[i+1])){
                        if(s[i+1] == '0')
                            s.replace(i, 3, "0");
                        else if(s[i+1] == '1')
                            s.replace(i, 3, "1");
                        else
                            throw Eccezione("Espressione non valida");
                    } else {
                        for(unsigned int j = 0; j < vars->size(); ++j)
                            if(vars->operator [](j).first == s[i+1])
                                op1 = vars->operator [](j).second;
                        if(op1 == 0)
                            s.replace(i, 3, "0");
                        else if(op1 == 1)
                            s.replace(i, 3, "1");
                        else
                            throw Eccezione("Espressione non valida");
                    }
                }
                ++i;
                break;

            case ')':
                if(indexParentesi > i)
                    throw Eccezione("Espressione non valida");
                else if(!isSymbol(s[i-1]) && s[i-2] == '(') {
                        if(isdigit(s[i-1])){
                            if(s[i-1] == '0')
                                s.replace(i-2, 3, "0");
                            else if(s[i-1] == '1')
                                s.replace(i-2, 3, "1");
                            else
                                throw Eccezione("Espressione non valida");
                        } else {
                            for(unsigned int j = 0; j < vars->size(); ++j)
                                if(vars->operator [](j).first == s[i-1])
                                    op1 = vars->operator [](j).second;
                            if(op1 == 0)
                                s.replace(i-2, 3, "0");
                            else if(op1 == 1)
                                s.replace(i-2, 3, "1");
                            else
                                throw Eccezione("Espressione non valida");
                        }
                } else
                    i++;
            break;
            case '|':
            {
                if(i == 0 || (isSymbol(s[i-1]) && !(s[i-1] == ')' && indexParentesi < i))) //Controllo carattere precedente
                    throw Eccezione("Espressione non valida");
                if(isSymbol(s[i+1])) {
                    if(s[i+1] == '!')
                    {
                        unsigned int j = 1;
                        while(s[i+j] == '!') j++; //Conta quanti ! ci sono + 1
                        if(s[i+j] == '(') {
                            indexParentesi = i+j;
                            i = indexParentesi + 1;
                            break;
                        } else if (isSymbol(s[i+j]))
                            throw Eccezione("Espressione non valida");
                        else { //Calcola "!.. A"
                            bool b = evaluate(s.substr(i+1,j));
                            s.replace(i+1, j, b ? "1" : "0");
                            break;
                        }
                    } else if(s[i+1] == '(') {
                            indexParentesi = i + 1;
                            i = indexParentesi + 1;
                            break;
                    } else
                        throw Eccezione("Espressione non valida");
                } else if(s[i-1] == ')') {
                    if(s[indexParentesi] != '(') {
                        indexParentesi = 0;
                        i = 0;
                    } else
                        i = indexParentesi;
                }
                //Non è un simbolo
                if(isdigit(s[i-1]))
                {
                    if(s[i-1] == '1')
                        op1 = true;
                    else if(s[i-1] == '0')
                        op1 = false;
                    else
                        throw Eccezione("Espressione non valida");
                } else
                    for(unsigned int j = 0; j < vars->size(); ++j)
                        if(vars->operator [](j).first == s[i-1])
                            op1 = vars->operator [](j).second;
                if(isdigit(s[i+1]))
                {
                    if(s[i+1] == '1')
                        op2 = true;
                    else if(s[i+1] == '0')
                        op2 = false;
                    else
                        throw Eccezione("Espressione non valida");
                } else
                    for(unsigned int j = 0; j < vars->size(); ++j){
                        if(vars->operator [](j).first == s[i+1])
                            op2 = vars->operator [](j).second;
                    }
                s.replace(i-1, 3, op1|op2 ? "1" : "0");
                break;
            }
            case '&':
            {
                if(i == 0 || (isSymbol(s[i-1]) && !(s[i-1] == ')' && indexParentesi < i))) //Controllo carattere precedente
                    throw Eccezione("Espressione non valida");
                if(isSymbol(s[i+1])) {
                    if(s[i+1] == '!')
                    {
                        unsigned int j = 1;
                        while(s[i+j] == '!') j++; //Conta quanti ! ci sono + 1
                        if(s[i+j] == '(') {
                            indexParentesi = i+j;
                            i = indexParentesi + 1;
                            break;
                        } else if (isSymbol(s[i+j]))
                            throw Eccezione("Espressione non valida");
                        else { //Calcola "!.. A"
                            bool b = evaluate(s.substr(i+1,j));
                            s.replace(i+1,j, b ? "1" : "0");
                            break;
                        }
                    } else if(s[i+1] == '(') {
                            indexParentesi = i + 1;
                            i = indexParentesi + 1;
                            break;
                    } else
                        throw Eccezione("Espressione non valida");
                } else if(s[i-1] == ')') {
                    if(s[indexParentesi] != '(') {
                        indexParentesi = 0;
                        i = 0;
                    } else
                        i = indexParentesi;
                    break;
                }
                //Non è un simbolo
                if(isdigit(s[i-1]))
                {
                    if(s[i-1] == '1')
                        op1 = true;
                    else if(s[i-1] == '0')
                        op1 = false;
                    else
                        throw Eccezione("Espressione non valida");
                } else //è una variabile
                    for(unsigned int j = 0; j < vars->size(); ++j)
                        if(vars->operator [](j).first == s[i-1])
                            op1 = vars->operator [](j).second;
                if(isdigit(s[i+1]))
                {
                    if(s[i+1] == '1')
                        op2 = true;
                    else if(s[i+1] == '0')
                        op2 = false;
                    else
                        throw Eccezione("Espressione non valida");
                } else
                    for(unsigned int j = 0; j < vars->size(); ++j)
                        if(vars->operator [](j).first == s[i+1])
                            op2 = vars->operator [](j).second;
                s.replace(i-1,3, op1&op2 ? "1" : "0");
                break;
            }
            case '!':
            {
                if(i > 0 && (s[i-1] == ')' || !isSymbol(s[i-1])))
                    throw Eccezione("Espressione non valida");
                unsigned int j = 0;
                while(s[i+j] == '!') j++; //Conta quanti ! ci sono + 1
                if(s[i+j] == '(') {
                    indexParentesi = i+j;
                    i = indexParentesi + 1;
                    break;
                } else if (i+j < s.length() && isSymbol(s[i+j]))
                    throw Eccezione("Espressione non valida");
                //Calcola "!.. A"
                bool b = false;
                if(i+j >= s.length())
                    throw Eccezione("Espressione non valida");
                if (!isdigit(s[i+j])) {
                    for(unsigned int x = 0; x < vars->size(); ++x)
                        if(vars->operator [](x).first == s[i+j])
                            b = vars->operator [](x).second;
                } else if (s[i+j] == '1')
                    b = true;
                else if (s[i+j] == '0')
                    b = false;
                else
                    throw Eccezione("Espressione non valida");
                if(j % 2 == 1)
                    b = !b;
                s.replace(i,j+1, b ? "1" : "0");
                break;
            }
            default:
                ++i;
        }
    }
    if(isdigit(s[0])){
        if(s[0] == '1')
            return true;
        if(s[0] == '0')
            return false;
        throw Eccezione("Espressione non valida");
    } else {
        if(vars->size() > 0) {
        for(unsigned int j = 0; j < vars->size(); ++j)
            if(vars->operator [](j).first == s[i])
                return vars->operator [](i).second;
        }
        else
           throw Eccezione("Espressione non valida");
    }
    return 0;
}

Result* Logica::calculate()
{
    if(text == "")
        return nullptr;
    //Controlla se ci sono stringhe di variabili es. AA
    for(unsigned int i = 1; i < text.length(); ++i)
        if (!isSymbol(text[i-1]) && !isSymbol(text[i]))
            throw Eccezione("Espressione non valida");
    if(!checkParentesi())
        throw Eccezione("Espressione non valida");

    //Carica le variabili-0
    for(unsigned int i = 0; i < text.length(); ++i)
        if(!isSymbol(text[i])){
            bool found = false;
            for(unsigned int j = 0; !found && j < vars->size(); ++j)
                if(vars->operator [](j).first == text[i])
                    found = true;
            if(!found && !isdigit(text[i]))
                vars->push_back(std::make_pair(text[i], 0));
        }
    std::sort(vars->begin(), vars->end());
    std::vector<std::vector<bool>> ris;
    for(unsigned int i = 0; i < pow(2, vars->size()); ++i)
        ris.push_back(std::vector<bool>());
    //Calcolo tabella verità
    unsigned int n = 0;
    do {
        for(unsigned int i = 0; i < vars->size(); ++i) //Carica input tabella verità
            ris[n].push_back(vars->operator [](i).second);
        ris[n].push_back(evaluate(text)); //Calcola output riga tabella

        for(unsigned int j = 0; j < vars->size(); ++j) //Cambia input
            if(vars->operator [](j).second == 0) {
                vars->operator [](j).second = 1;
                break;
            } else
                vars->operator [](j).second = 0;
    } while (++n < pow(2, vars->size()));

    std::vector<char> columnsName;
    for(unsigned int i = 0; i < vars->size(); ++i)
        columnsName.push_back((*vars)[i].first);

    result = new LogicalResult(ris, columnsName);
    return result;
}
