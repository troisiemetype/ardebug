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

#include "graphview.h"
#include "ui_graphview.h"

GraphView::GraphView(QWidget *parent, vector<Pair*> *pairs) :
    QDialog(parent),
    ui(new Ui::GraphView)
{
    ui->setupUi(this);

    this->setGeometry(550, 50, 600, 400);

    pairsList = pairs;

    for(int i = 0; i < pairsList->size(); i++)
    {
        QCheckBox *var = new QCheckBox(pairsList->at(i)->getName(), this);
        ui->varsLayout->addWidget(var);
    }

    curvesScene = new QGraphicsScene();
    curvesScene->setSceneRect(0, 0, 500, 500);

    curvesView = new QGraphicsView(curvesScene);

    ui->mainLayout->addWidget(curvesView);

    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    timer->start(100);

}

GraphView::~GraphView()
{
    delete ui;
}

void GraphView::update()
{

}

/*
    for(int i = 0; i < varNumber; i++){
        varList.at(i)->updateCurve(currentX);
        curvesScene->removeItem(pathList.at(i));
        QGraphicsPathItem *path = curvesScene->addPath(varList.at(i)->getPath(),
                                                       varList.at(i)->getPenStyle());
        pathList.erase(pathList.begin()+i);
        pathList.insert(pathList.begin()+i, path);
    }
*/
