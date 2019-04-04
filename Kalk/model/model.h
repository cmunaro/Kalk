#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include "espressione.h"
#include "aritmetica.h"
#include "funzione.h"
#include "logica.h"

class Model
{
private:
    Aritmetica* aritmetica;
    Funzione* funzione;
    Logica* logica;

public:
    Model();
    void addLogicaChar(const char);
    void addAritmeticaChar(const char);
    void addFunzioneChar(const char);
    void addLogicaInt(const int);
    void addAritmeticaInt(const int);
    void addFunzioneInt(const int);
    std::string getLogicaText() const;
    std::string getAritmeticaText() const;
    std::string getFunzioneText() const;
    void calculateLogica();
    void calculateAritmetica();
    void calculateFunzione();
    std::vector<std::vector<char>> getResultLogica() const;
    double getResultAritmetica() const;
    std::vector<std::pair<double, double>> getResultFuzione() const;
    void clearLogica();
    void clearAritmetica();
    void clearFunzione();
    void cancLogica();
    void cancAritmetica();
    void cancFunzione();
    double doubleFromLogica() const;
    double doubleFromAritmetica() const;
    double doubleFromFunzione() const;

};

#endif // MODEL_H
