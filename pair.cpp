#include "pair.h"

Pair::Pair()
{

}

Pair::Pair(QGridLayout *layout, QString _name)
{
//    parent = _parent;
    parentLayout = layout;
    bool firstTime = true;
    pause = false;
    valuesSize = 255;
    name = _name;
    createWidget();
    clear();
}

Pair::~Pair()
{

}

void Pair::update(int val)
{
    value = val;

    if(firstTime == true){
        firstTime = false;
        minValue = val;
        maxValue = val;
    }

    if(val <= minValue){
        minValue = val;
    }

    if(val >= maxValue){
        maxValue = val;
    }

    if(!pause){
        updateGui();
    }

    values.push_back(val);

    if(values.size() > valuesSize){
        values.erase(values.begin());
    }
}

void Pair::updateGui(){
    valueLabel->setText(QString::number(value));
    minLabel->setText(QString::number(minValue));
    maxLabel->setText(QString::number(maxValue));
}

void Pair::clear()
{
    firstTime = true;
    value = 0;
    minValue = 0;
    maxValue = 0;
    values.clear();

    updateGui();
}

void Pair::createWidget()
{
    nameLabel = new QLabel(name);
    valueLabel = new QLineEdit(QString::number(value));
    minLabel = new QLineEdit(QString::number(minValue));
    maxLabel = new QLineEdit(QString::number(maxValue));

    pauseButton = new QPushButton("Pause");
    clearButton = new QPushButton("clear");
    optionButton = new QPushButton("options");

    pauseButton->setCheckable(true);

    valueLabel->setReadOnly(true);
    minLabel->setReadOnly(true);
    maxLabel->setReadOnly(true);

    valueLabel->setMinimumWidth(50);
    minLabel->setMinimumWidth(50);
    maxLabel->setMinimumWidth(50);

    valueLabel->setAlignment(Qt::AlignRight);
    minLabel->setAlignment(Qt::AlignRight);
    maxLabel->setAlignment(Qt::AlignRight);

    int row = parentLayout->rowCount();

    parentLayout->addWidget(nameLabel, row, 0);
    parentLayout->addWidget(valueLabel, row, 2);
    parentLayout->addWidget(minLabel, row, 3);
    parentLayout->addWidget(maxLabel, row, 4);

    parentLayout->addWidget(pauseButton, row, 1);
    parentLayout->addWidget(clearButton, row, 5);
    parentLayout->addWidget(optionButton, row, 6);

    QObject::connect(pauseButton, SIGNAL(clicked(bool)), this, SLOT(on_pauseButton_clicked(bool)));
    QObject::connect(clearButton, SIGNAL(pressed()), this, SLOT(on_clearButton_pressed()));
    QObject::connect(optionButton, SIGNAL(pressed()), this, SLOT(on_optionButton_pressed()));

}

QString Pair::getName()
{
    return name;
}

void Pair::on_pauseButton_clicked(bool checked)
{
    pause = checked;
}

void Pair::on_clearButton_pressed()
{
    clear();
}

void Pair::on_optionButton_pressed()
{

}


