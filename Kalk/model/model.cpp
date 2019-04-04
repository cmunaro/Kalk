#include "model.h"

Model::Model()
{
    aritmetica = new Aritmetica();
    funzione = new Funzione();
    logica = new Logica("");
}

void Model::addLogicaChar(const char c)
{
    logica = new Logica((*logica) + c);
}

void Model::addAritmeticaChar(const char c)
{
    aritmetica = new Aritmetica((*aritmetica) + c);
}

void Model::addFunzioneChar(const char c)
{
    funzione = new Funzione((*funzione) + c);
}

std::string Model::getLogicaText() const
{
    std::string asd = logica->getText();
    return asd;
}

std::string Model::getAritmeticaText() const
{
    return aritmetica->getText();
}

std::string Model::getFunzioneText() const
{
    return funzione->getText();
}

void Model::calculateLogica()
{
    logica->calculate();
}

void Model::calculateAritmetica()
{
    aritmetica->calculate();
}

void Model::calculateFunzione()
{
    funzione->calculate();
}

std::vector<std::vector<char>> Model::getResultLogica() const
{
    LogicalResult *lr = dynamic_cast<LogicalResult *>(logica->getResult());
    std::vector<std::vector<char>> ris;
    ris.push_back(lr->getColumnNames());
    std::vector<std::vector<bool>> matrix = lr->getMatrix();
    for(auto i = matrix.begin(); i != matrix.end(); ++i) {
        std::vector<char> vc;
        for(auto j = i->begin(); j != i->end(); ++j)
            vc.push_back(static_cast<char>(*j + 0x30));
        ris.push_back(vc);
    }
    return ris;
}

double Model::getResultAritmetica() const
{
    return dynamic_cast<AritmeticResult *>(aritmetica->getResult())->getValue();
}

std::vector<std::pair<double, double>> Model::getResultFuzione() const
{
    return dynamic_cast<FunctionResult *>(funzione->getResult())->getPoints();
}

void Model::clearLogica()
{
    logica = new Logica();
}

void Model::clearAritmetica()
{
    aritmetica = new Aritmetica();
}

void Model::clearFunzione()
{
    funzione = new Funzione();
}

void Model::cancLogica()
{
    logica = new Logica(--(*logica));
}

void Model::cancAritmetica()
{
    aritmetica = new Aritmetica(--(*aritmetica));
}

void Model::cancFunzione()
{
    funzione = new Funzione(--(*funzione));
}

double Model::doubleFromLogica() const
{
    return logica->operator double();
}

double Model::doubleFromAritmetica() const
{
    return aritmetica->operator double();
}

double Model::doubleFromFunzione() const
{
    return funzione->operator double();
}

void Model::addLogicaInt(const int n)
{
    if(n != 0)
        logica = new Logica((*logica) + n);
}

void Model::addAritmeticaInt(const int n)
{
    if(n != 0)
        aritmetica = new Aritmetica((*aritmetica) + n);
}

void Model::addFunzioneInt(const int n)
{
    if(n != 0)
        funzione = new Funzione((*funzione) + n);
}
