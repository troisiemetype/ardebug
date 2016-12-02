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

#include "varsettings.h"
#include "ui_varsettings.h"

VarSettings::VarSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VarSettings)
{
    ui->setupUi(this);

    varTypes << "string" << "int" << "float" << "bool";// << "binary" << "hexadecimal";
    plotTypes << "no pen" << "solid" << "dash" << "dot" <<
                 "dash dot" << "dash dot dot";
    colorTypes << "color 0" << "color 1" << "black" << "white" <<
                  "dark gray" << "gray" << "lightGray" << "red" <<
                  "green" << "blue" << "cyan" << "magenta" <<
                  "yellow" << "dark red"  << "darkGreen" << "dark blue" <<
                  "dark cyan" << "dark magenta" << "dark yellow";


    ui->varTypeComboBox->addItems(varTypes);
    ui->plotStyleComboBox->addItems(plotTypes);
    for(int i = 0; i<17; i++)
    {
        QPixmap pixmap = QPixmap(15, 15);
        pixmap.fill(Qt::GlobalColor(i));
        QIcon icon = QIcon(pixmap);
        ui->colorComboBox->addItem(icon, colorTypes.at(i));
    }
}

VarSettings::~VarSettings()
{
    delete ui;
}

QString VarSettings::getName()
{
    return name;
}

void VarSettings::setName(QString val)
{
    name = val;
    ui->nameLineEdit->setText(name);
}

int VarSettings::getVarType()
{
    return varType;
}

void VarSettings::setVarType(int val)
{
    varType = val;
    ui->varTypeComboBox->setCurrentIndex(varType);
}

int VarSettings::getPlotStyle()
{
    return plotStyle;
}

void VarSettings::setPlotStyle(int val)
{
    plotStyle = val;
    ui->plotStyleComboBox->setCurrentIndex(plotStyle);
}

int VarSettings::getPlotSize()
{
    return plotSize;
}

void VarSettings::setPlotSize(int val)
{
    plotSize = val;
    ui->plotSizeSpinBox->setValue(plotSize);
}

int VarSettings::getColor()
{
    return plotColor;
}

void VarSettings::setColor(int val)
{
    plotColor = val;
    ui->colorComboBox->setCurrentIndex(plotColor);
}

bool VarSettings::getSuppress()
{
    return suppress;
}

void VarSettings::on_buttonBox_accepted()
{
    if(ui->nameLineEdit->text() != ""){
        name = ui->nameLineEdit->text();
    }
    varType = ui->varTypeComboBox->currentIndex();
    plotColor = ui->colorComboBox->currentIndex();
    plotStyle = ui->plotStyleComboBox->currentIndex();
    plotSize = ui->plotSizeSpinBox->value();

    suppress = ui->suppressCheckBox->checkState();
}

void VarSettings::on_buttonBox_rejected()
{

}
