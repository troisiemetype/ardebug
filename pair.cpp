//ARDEBUG
/*
 * This program is intended to help debug Arduino programs
 * Copyright (C) 2016  Pierre-Loup Martin / Le labo du troisième
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pair.h"

Pair::Pair()
{

}

Pair::Pair(QWidget *_parent, QGridLayout *layout, QString _name)
{
    parent = _parent;
    parentLayout = layout;

    type = 1;
    plotColor = 2;
    plotStyle = 1;
    plotSize = 1;


//    on_optionButton_clicked();

    firstTime = true;
    pause = false;
    valuesSize = 255;
    name = _name;
    curvePath = new QPainterPath();
    penStyle = new QPen();
    createWidget();
    clear();

    connect(this, SIGNAL(on_delete(Pair*)), parent, SLOT(on_pair_delete(Pair*)));
}

Pair::~Pair()
{
    delete nameLabel;
    delete valueLabel;
    delete minLabel;
    delete maxLabel;

    delete pauseButton;
    delete clearButton;
    delete optionButton;

}

//Handle the update of the values. Called by the serial.readyRead() interrupt
void Pair::update(int val, int posX)
{
    value = val;


    if(firstTime == true){
        curvePath->moveTo(posX, val);
        firstTime = false;
        minValue = val;
        maxValue = val;
        prevX = posX;
        prevY = val;

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

//Update the GUI display values
void Pair::updateGui(){
    valueLabel->setText(QString::number(value));
    minLabel->setText(QString::number(minValue));
    maxLabel->setText(QString::number(maxValue));
}

//Update the curve path
void Pair::updateCurve(int posX)
{
    curvePath->lineTo(posX, value);

}

//Get the curve path
QPainterPath Pair::getPath()
{
    return *curvePath;
}

//Get the pen style
QPen Pair::getPenStyle()
{
    return *penStyle;
}

//Set the pen style
void Pair::setPenStyle()
{
    color = Qt::GlobalColor(plotColor);
    penStyle->setColor(color);
    penStyle->setStyle(Qt::PenStyle(plotStyle));
    penStyle->setWidth(plotSize);
    penStyle->setCapStyle(Qt::RoundCap);
    penStyle->setJoinStyle(Qt::RoundJoin);
}

//Init the values
void Pair::clear()
{
    firstTime = true;
    value = 0;
    minValue = 0;
    maxValue = 0;
    values.clear();

    updateGui();
}

//Add a new var to the GUI
void Pair::createWidget()
{
    nameLabel = new QLabel(name);
    valueLabel = new QLineEdit(QString::number(value));
    minLabel = new QLineEdit(QString::number(minValue));
    maxLabel = new QLineEdit(QString::number(maxValue));

    pauseButton = new QPushButton("pause");
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
    QObject::connect(clearButton, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));
    QObject::connect(optionButton, SIGNAL(clicked()), this, SLOT(on_optionButton_clicked()));

}

//Get the var name
QString Pair::getName()
{
    return name;
}

//Get the last value
int Pair::getValue()
{
    return value;
}

//Slot for the pause button
void Pair::on_pauseButton_clicked(bool checked)
{
    pause = checked;
    pauseButton->setChecked(checked);
}

//Slot for the clear button
void Pair::on_clearButton_clicked()
{
    clear();
}

//Slot for the option button
void Pair::on_optionButton_clicked()
{
    VarSettings settings(parent);

    settings.setName(name);
    settings.setVarType(type);
    settings.setColor(plotColor);
    settings.setPlotSize(plotSize);
    settings.setPlotStyle(plotStyle);

    if(settings.exec())
    {
        name = settings.getName();
        type = settings.getVarType();
        plotColor = settings.getColor();
        plotSize = settings.getPlotSize();
        plotStyle = settings.getPlotStyle();

        nameLabel->setText(name);
        setPenStyle();

        if(settings.getSuppress()){
            emit on_delete(this);
        }
    }
}


