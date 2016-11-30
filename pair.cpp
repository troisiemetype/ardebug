#include "pair.h"

Pair::Pair()
{

}

Pair::Pair(QGridLayout *_parent, QString _name)
{
    parentLayout = _parent;
    name = _name;
    value = 0;
    minValue = 0;
    maxValue = 0;

    createWidget();
}

Pair::~Pair()
{

}

void Pair::update()
{

}

void Pair::createWidget()
{
    nameLabel = new QLabel(name);
    valueLabel = new QLabel(QString(value));
    minLabel = new QLabel(QString(minValue));
    maxLabel = new QLabel(QString(maxValue));

    clearButton = new QPushButton("clear");
    optionButton = new QPushButton("options");

    parentLayout->addWidget(nameLabel, 1, 0);
    parentLayout->addWidget(valueLabel, 1, 1);
    parentLayout->addWidget(minLabel, 1, 2);
    parentLayout->addWidget(maxLabel, 1, 3);

    parentLayout->addWidget(clearButton, 1, 4);
    parentLayout->addWidget(optionButton, 1, 5);
}
