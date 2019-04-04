#include <iostream>
#include <aritmetica.h>
#include <logica.h>
#include <funzione.h>

int main()
{
    Espressione* e;
    e = new Logica("(!(B|(A))&!C)");
    try {
        e->calculate();
    } catch (Eccezione e) {
        std::cout << e.getError() << std::endl;
    }
    Result *r = e->getResult();
    r->stampa();
    std::cout << "\n\n\n";

    e = new Aritmetica("2+3-1");
    try {
        e->calculate();
    } catch (Eccezione e) {
        std::cout << e.getError() << std::endl;
    }
    r = e->getResult();
    r->stampa();
    std::cout << "\n\n\n";

    e = new Funzione("x*x=y");
    try {
        e->calculate();
    } catch (Eccezione e) {
        std::cout << e.getError() << std::endl;
    }
    r = e->getResult();
    r->stampa();

    return 0;
}
