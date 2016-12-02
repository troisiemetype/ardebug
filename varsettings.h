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

#ifndef VARSETTINGS_H
#define VARSETTINGS_H

#include <QColor>
#include <QDialog>
#include <QMetaObject>
#include <QMetaType>
#include <QString>
#include <QStringList>

#include "pair.h"

namespace Ui {
class VarSettings;
}

class VarSettings : public QDialog
{
    Q_OBJECT


public:
    explicit VarSettings(QWidget *parent = 0);
    ~VarSettings();

    QString getName();
    void setName(QString);

    int getVarType();
    void setVarType(int);

    int getPlotStyle();
    void setPlotStyle(int);

    int getPlotSize();
    void setPlotSize(int);

    int getColor();
    void setColor(int);

    bool getSuppress();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::VarSettings *ui;

    QStringList varTypes;
    QStringList plotTypes;
    QStringList colorTypes;

    QString name;
    int varType;
    int plotColor;
    int plotStyle;
    int plotSize;

    bool suppress;

};

#endif // VARSETTINGS_H
