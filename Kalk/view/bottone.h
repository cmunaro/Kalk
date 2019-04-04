#ifndef BOTTONE_H
#define BOTTONE_H

#include <QToolButton>

class Bottone : public QToolButton
{
    Q_OBJECT

public:
    explicit Bottone(const QString &text, QWidget *parent = nullptr);

};

#endif // BOTTONE_H
