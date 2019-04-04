#include "view/kalk.h"
#include "view/kalk.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Kalk k;
    k.show();
    return app.exec();
}
