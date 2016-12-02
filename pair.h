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

#ifndef PAIR_H
#define PAIR_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include <iostream>
#include <vector>

#include "varsettings.h"

#define TYPE_STRING     0
#define TYPE_INT        1
#define TYPE_FLOAT      2
#define TYPE_BOOL       3
#define TYPE_BIN        4
#define TYPE_HEX        5

using namespace std;
class Pair : public QObject
{
    Q_OBJECT

public:
    Pair();
    ~Pair();

    Pair(QWidget*, QGridLayout*, QString);

    void update(int, int);
    void updateGui();
    void clear();

    void createWidget();

    QString getName();
    int getValue();
    void updateCurve(int);
    QPainterPath getPath();

    QPen getPenStyle();

    void setPenStyle();

private:

    QWidget *parent;
    QGridLayout *parentLayout;

    bool firstTime;
    bool pause;
    QString name;

    int type;
    int plotColor;
    int plotStyle;
    int plotSize;

    int value;
    int minValue;
    int maxValue;
    vector<int> values;

    int prevX;
    int prevY;

    int valuesSize;

    QPainterPath *curvePath;

    QPen *penStyle;
    QColor color;

    QLabel *nameLabel;
    QLineEdit *valueLabel;
    QLineEdit *minLabel;
    QLineEdit *maxLabel;

    QPushButton *pauseButton;
    QPushButton *clearButton;
    QPushButton *optionButton;

public slots:

    void on_pauseButton_clicked(bool);

    void on_clearButton_clicked();

protected slots:

    void on_optionButton_clicked();

};

#endif // PAIR_H
