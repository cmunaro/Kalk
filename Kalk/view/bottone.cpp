#include "view/bottone.h"

Bottone::Bottone(const QString &text, QWidget *parent) : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
    QFont font = this->font();
    font.setPointSize(15);
    setFont(font);
    setMinimumHeight(50);
    setMinimumWidth(50);
}
