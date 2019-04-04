#include "view/kalk.h"

#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QTabWidget>
#include <string>

#include "plotwidget.h"
#include "tablewidget.h"
#include "model/eccezione.h"

Kalk::Kalk(QMainWindow *parent) : QMainWindow(parent)
{
    model = new Model();

    inizializzaToolBar();
    inizializzaLayouts();

    display = new QLineEdit("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(25);
    QFont font = display->font();
    font.setPointSize(20);
    display->setFont(font);

    QWidget *tabLogica = new QWidget;
    tabLogica->setLayout(LayoutLogica);
    QWidget *tabAritmetica = new QWidget;
    tabAritmetica->setLayout(LayoutAritmentica);
    QWidget *tabFunzione = new QWidget;
    tabFunzione->setLayout(LayoutFunzionale);

    tab = new QTabWidget(this);
    tab->setTabPosition(QTabWidget::South);
    tab->addTab(tabLogica, "Logica");
    tab->addTab(tabAritmetica, "Aritmentica");
    tab->addTab(tabFunzione, "Funzione");
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(showHint()));
    setCentralWidget(tab);
    lastIndex = 0;
    tab->setCurrentIndex(lastIndex);

    QWidget *mainWidget = new QWidget;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(display, 0, 0, 1, 4);
    Bottone *b = new Bottone("Clear");
    connect(b, SIGNAL(clicked()), this, SLOT(clickCancella()));
    mainLayout->addWidget(b, 1, 0, 1, 2);
    b = new Bottone("Canc");
    connect(b, SIGNAL(clicked()), this, SLOT(clickCanc()));
    mainLayout->addWidget(b, 1, 2, 1, 2);
    mainLayout->addWidget(tab, 2, 0, 1, 4);

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

Bottone* Kalk::creaBottone(const QString& s)
{
    Bottone* b = new Bottone(s);
    if(s != "=") {
        connect(b, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(b, s);
    } else {
        connect(b, SIGNAL(clicked()), this, SLOT(clickUguale()));
    }
    return b;
}

void Kalk::clickSimbolo(const QString &s)
{
    char c = s.toUtf8().data()[0];

    try {
        switch (tab->currentIndex()) {
            case 0: //Logica
                model->addLogicaChar(c);
                display->setText(QString(model->getLogicaText().data()));
                break;
            case 1: //Aritmetica
                model->addAritmeticaChar(c);
                display->setText(QString(model->getAritmeticaText().data()));
                break;
            case 2: //Funzione
                model->addFunzioneChar(c);
                display->setText(QString(model->getFunzioneText().data()));
                break;
        }
    } catch (Eccezione e) {
        QMessageBox::information(
            this,
            tr("Errore"),
            tr(e.getError().data())
            );
    }

}

void Kalk::clickUguale()
{
    std::vector<std::vector<char>> lr;
    std::string ar;
    std::vector<std::pair<double, double>> fr;

    try {
        switch (tab->currentIndex()) {
        case 0: //Logica
            if(model->getLogicaText() != "") {
                model->calculateLogica();
                lr = model->getResultLogica();
                TableWidget *table = new TableWidget(nullptr, &lr, this->size(),this->pos());
                table->show();
            }
            break;
        case 1: //Aritmetica
            if(model->getAritmeticaText() != "") {
                model->calculateAritmetica();
                ar = std::to_string(model->getResultAritmetica());
                ar.erase(ar.find_last_not_of('0') + 1, std::string::npos);
                if(ar[ar.length() - 1] == '.')
                    ar = ar.substr(0, ar.length() - 1);
                display->setText(QString(ar.data()));
            }
            break;
        case 2: //Funzione
            if(model->getFunzioneText() != "") {
                model->calculateFunzione();
                fr = model->getResultFuzione();
                PlotWidget *plot = new PlotWidget(nullptr, &fr, this->size(), this->pos());
                plot->show();
            }
            break;
        }
    } catch (Eccezione e) {
        QMessageBox::information(
            this,
            tr("Errore"),
            tr(e.getError().data())
            );
    }
}

void Kalk::clickCancella()
{
    switch (tab->currentIndex()) {
    case 0: //Logica
        model->clearLogica();
        break;
    case 1: //Aritmetica
        model->clearAritmetica();
        break;
    case 2: //Funzione
        model->clearFunzione();
        break;
    }
    display->setText("0");
}

void Kalk::clickCanc()
{
    switch (tab->currentIndex()) {
    case 0: //Logica
        model->cancLogica();
        display->setText(QString(model->getLogicaText().data()));
        break;
    case 1: //Aritmetica
        model->cancAritmetica();
        display->setText(QString(model->getAritmeticaText().data()));
        break;
    case 2: //Funzione
        model->cancFunzione();
        display->setText(QString(model->getFunzioneText().data()));
        break;
    }
    if(display->text() == "")
        display->setText("0");
}

void Kalk::close()
{
    exit(0);
}

void Kalk::changeTab(int index)
{
    int pass = 0;
    try {
        switch(lastIndex) {
            case 0:
                pass = static_cast<int>(model->doubleFromLogica());
                break;
            case 1:
                pass = static_cast<int>(model->doubleFromAritmetica());
                break;
            case 2:
                pass = static_cast<int>(model->doubleFromFunzione());
                break;
        }
        lastIndex = index;
        switch (index) {
            case 0: //Logica
                model->addLogicaInt(pass);
                display->setText(QString(model->getLogicaText().data()));
                break;
            case 1: //Aritmetica
                model->addAritmeticaInt(pass);
                display->setText(QString(model->getAritmeticaText().data()));
                break;
            case 2: //Funzione
                model->addFunzioneInt(pass);
                display->setText(QString(model->getFunzioneText().data()));
                break;
        }
    } catch (Eccezione e) {
        QMessageBox::information(
            this,
            tr("Errore"),
            tr(e.getError().data())
            );
    }
    if(display->text() == "")
        display->setText("0");
}

void Kalk::showHint()
{
    QMessageBox::information(
        this,
        tr("Informazioni"),
        tr("Quando si cambia tab, se il risultato non è nullo, esso sarà sommato all'input della tab successiva")
        );
    if (hint) {
        hint = false;
        disconnect(tab, SIGNAL(currentChanged(int)), this, SLOT(showHint()));
    }
}

void Kalk::inizializzaToolBar()
{
    QMenu *menu = menuBar()->addMenu(tr("File"));
    menu->addAction(tr("Exit"), this, SLOT(close()));

    menu = menuBar()->addMenu(tr("Help"));
    menu->addAction(tr("Show Info"), this, SLOT(showHint()));
}

void Kalk::inizializzaLayouts()
{
    mapper = new QSignalMapper(this);

    LayoutLogica = new QGridLayout;
    LayoutLogica->addWidget(creaBottone("&&"), 0, 0, 1, 1);
    LayoutLogica->addWidget(creaBottone("|"), 0, 1, 1, 1);
    LayoutLogica->addWidget(creaBottone("!"), 0, 2, 1, 1);
    LayoutLogica->addWidget(creaBottone("("), 0, 3, 1, 1);
    LayoutLogica->addWidget(creaBottone("A"));
    LayoutLogica->addWidget(creaBottone("B"));
    LayoutLogica->addWidget(creaBottone("C"));
    LayoutLogica->addWidget(creaBottone(")"));
    LayoutLogica->addWidget(creaBottone("D"));
    LayoutLogica->addWidget(creaBottone("E"));
    LayoutLogica->addWidget(creaBottone("F"));
    LayoutLogica->addWidget(creaBottone("0"), 3, 0, 1, 1);
    LayoutLogica->addWidget(creaBottone("1"), 3, 1, 1, 1);
    LayoutLogica->addWidget(creaBottone("="), 3, 3, 1, 1);

    LayoutAritmentica = new QGridLayout();
    LayoutAritmentica->addWidget(creaBottone("1"), 0, 0, 1, 1);
    LayoutAritmentica->addWidget(creaBottone("2"), 0, 1, 1, 1);
    LayoutAritmentica->addWidget(creaBottone("3"), 0, 2, 1, 1);
    LayoutAritmentica->addWidget(creaBottone("+"), 0, 3, 1, 1);
    LayoutAritmentica->addWidget(creaBottone("4"));
    LayoutAritmentica->addWidget(creaBottone("5"));
    LayoutAritmentica->addWidget(creaBottone("6"));
    LayoutAritmentica->addWidget(creaBottone("-"));
    LayoutAritmentica->addWidget(creaBottone("7"));
    LayoutAritmentica->addWidget(creaBottone("8"));
    LayoutAritmentica->addWidget(creaBottone("9"));
    LayoutAritmentica->addWidget(creaBottone("*"));
    LayoutAritmentica->addWidget(creaBottone("0"));
    LayoutAritmentica->addWidget(creaBottone("("));
    LayoutAritmentica->addWidget(creaBottone(")"));
    LayoutAritmentica->addWidget(creaBottone("/"));
    LayoutAritmentica->addWidget(creaBottone("="), 4, 3, 1, 1);

    LayoutFunzionale = new QGridLayout;
    LayoutFunzionale->addWidget(creaBottone("1"), 0, 0, 1, 1);
    LayoutFunzionale->addWidget(creaBottone("2"), 0, 1, 1, 1);
    LayoutFunzionale->addWidget(creaBottone("3"), 0, 2, 1, 1);
    LayoutFunzionale->addWidget(creaBottone("+"), 0, 3, 1, 1);
    LayoutFunzionale->addWidget(creaBottone("4"));
    LayoutFunzionale->addWidget(creaBottone("5"));
    LayoutFunzionale->addWidget(creaBottone("6"));
    LayoutFunzionale->addWidget(creaBottone("-"));
    LayoutFunzionale->addWidget(creaBottone("7"));
    LayoutFunzionale->addWidget(creaBottone("8"));
    LayoutFunzionale->addWidget(creaBottone("9"));
    LayoutFunzionale->addWidget(creaBottone("*"));
    LayoutFunzionale->addWidget(creaBottone("0"));
    LayoutFunzionale->addWidget(creaBottone("("));
    LayoutFunzionale->addWidget(creaBottone(")"));
    LayoutFunzionale->addWidget(creaBottone("/"));
    LayoutFunzionale->addWidget(creaBottone("x"), 4, 2, 1, 1);
    LayoutFunzionale->addWidget(creaBottone("="), 4, 3, 1, 1);

    connect(mapper, SIGNAL(mapped(const QString &)), this, SLOT(clickSimbolo(const QString &)));
}
