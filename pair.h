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

    void update(QString, int);
    void updateGui();
    void clear();

    void createWidget();

    void setIndex(int);
    int getIndex();

    void setName(QString);
    QString getName();

private:
    //Parents
    QWidget *parent;
    QGridLayout *parentLayout;

    //Operation vars
    bool firstTime;
    bool pause;
    QString name;
    int index;

    //Data struct
    struct data_struct{
        QString val;
        int timestamp;
    };

    //Data table
    vector<data_struct> values;

    //Size of data taebl
    int valuesSize;

    //Graph parameters
    int type;
    int plotColor;
    int plotStyle;
    int plotSize;


    //last value received
    data_struct value;

    //Numerical values
    int numValue;
    int minValue;
    int maxValue;

    //Path, pen style and color
    //TODO: move from Pair to GraphView
    QPainterPath *curvePath;
    QPen *penStyle;
    QColor color;

    //GUI display widget pointers
    QLabel *nameLabel;
    QLineEdit *valueLabel;
    QLineEdit *minLabel;
    QLineEdit *maxLabel;

    QPushButton *pauseButton;
    QPushButton *clearButton;
    QPushButton *optionButton;

signals:

    //custom signal to propagate Pair delete to MainWindow
    void on_delete(Pair*);

    void on_update(Pair*);

public slots:

    //Slots for GUI buttons.
    void on_pauseButton_clicked(bool);

    void on_clearButton_clicked();

protected slots:

    void on_optionButton_clicked();

};

#endif // PAIR_H
