#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include <view/bottone.h>
#include "model/model.h"

class Kalk : public QMainWindow
{
    Q_OBJECT

private slots:
    void clickSimbolo(const QString &);
    void clickUguale();
    void clickCancella();
    void clickCanc();
    void close();
    void showHint();
    void changeTab(int);

private:
    QTabWidget* tab;
    std::vector<Bottone*> bottoni;
    QGridLayout* LayoutAritmentica;
    QGridLayout* LayoutLogica;
    QGridLayout* LayoutFunzionale;
    QLineEdit* display;
    bool hint = true;
    int lastIndex;

    Model* model;
    QSignalMapper *mapper;

    void inizializzaLayouts();
    void inizializzaToolBar();
    Bottone* creaBottone(const QString& s);

public:
    Kalk(QMainWindow *parent = nullptr);

};

#endif // MAINWINDOW_H
