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

#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QCheckBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDialog>
#include <QTimer>

#include <vector>

#include "pair.h"

namespace Ui {
class GraphView;
}

class GraphView : public QDialog
{
    Q_OBJECT

public:
    explicit GraphView(QWidget *parent = 0, vector<Pair*> *pairs = 0);
    ~GraphView();

public slots:
    void update();

private:
    Ui::GraphView *ui;

    QGraphicsScene *curvesScene;
    QGraphicsView *curvesView;


    vector<Pair*> *pairsList;


};

#endif // GRAPHVIEW_H
