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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    move(50, 50);

    currentX = 0;

    serial = new QSerialPort(this);
    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

    curvesScene = new QGraphicsScene();
    curvesScene->setSceneRect(0, 0, 500, 800);

    curvesView = new QGraphicsView(curvesScene);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//read a pair from the serial. Called by readData()
bool MainWindow::readPair()
{
    //Get the serial data pending
    char *data = new char();
    serial->readLine(data, 64);
    QString name = QString(data);

    //trim the end of line chars added by Serial.println() on Arduino
    name.remove(name.size()-2, 2);

    //Verifies if the var received match a var that is watched
    for(int i = 0; i < varList.size(); i++){
        //if yes, update value
        if(name == varList.at(i)->getName()){
            serial->readLine(data, 64);
            QString value = QString(data);
            varList.at(i)->update(value.toInt(), currentX);
            return true;
        }
    }
    return false;

}

//Slot for data available
void MainWindow::readData()
{
    if(varList.size() == 0)
    {
        serial->clear(QSerialPort::Input);
        return;
    }
    readPair();
}

//Slot for connecting serial
void MainWindow::on_actionConnect_triggered(bool checked)
{
    if(checked){
        if(serial->open(QIODevice::ReadOnly))
        {
        } else {
            ui->actionConnect->setChecked(false);
        }
    } else {
        serial->close();
    }

}

//Slot for openning the serial settings window
void MainWindow::on_actionPort_settings_triggered()
{
    SerialSettings serialSettings(this, serial);
    serialSettings.exec();

}

//slot for adding a new var
//TODO: add var type
void MainWindow::on_actionAdd_var_triggered()
{
    bool ok = 0;
    //get a name for an input box
    QString name = QInputDialog::getText(this, "New var", "Var name", QLineEdit::Normal, QString(), &ok);
    //Create a pair if name has benn set, and ok clicked
    if(ok && !name.isEmpty()){
        Pair *pair = new Pair(this, ui->pairsLayout, name);
        QGraphicsPathItem *path = curvesScene->addPath(pair->getPath());
        varList.push_back(pair);
        pathList.push_back(path);
//        QObject::connect(pair->clearButton, SIGNAL(pressed()), pair, SLOT(on_clearButton_pressed()));
    }
}

//slot for removing a var
//TODO: everything. it doesn't work for now
void MainWindow::on_actionRemove_var_triggered()
{
    int varNumber = varList.size();

    if(varNumber == 0)
    {
        return;
    }

    Dialog varListDialog(this);

    QWidget *widget = new QWidget;

    QGridLayout *layout = new QGridLayout;

    for(int i = 0; i < varNumber; i++){

        QCheckBox *check = new QCheckBox();
        layout->addWidget(check, i, 0);

        QLabel *name = new QLabel(varList.at(i)->getName());
        layout->addWidget(name, i, 1);
    }

    widget->setLayout(layout);

    varListDialog.layout()->addWidget(widget);
    varListDialog.exec();
}

//Slot to clear all the readings
void MainWindow::on_clearAllButton_clicked()
{
    int varNumber = varList.size();

    if(varNumber == 0)
    {
        return;
    }

    for(int i = 0; i < varNumber; i++){
        varList.at(i)->on_clearButton_clicked();
    }

}

//Slot to pause all the readings (but reading continues backstage)
void MainWindow::on_pauseAllButton_clicked(bool checked)
{
    int varNumber = varList.size();

    if(varNumber == 0)
    {
        return;
    }

    for(int i = 0; i < varNumber; i++){
        varList.at(i)->on_pauseButton_clicked(checked);
    }

}

//slot for timer. Used by the Graphics View update
//TODO: create a class to handle graphics, put the timer in it
void MainWindow::on_timer_timeout()
{
    int varNumber = varList.size();

    if(!serial->isOpen()){
        return;
    }

    if(varNumber == 0)
    {
        return;
    }

    currentX += 2;

    for(int i = 0; i < varNumber; i++){
        varList.at(i)->updateCurve(currentX);
        curvesScene->removeItem(pathList.at(i));
        QGraphicsPathItem *path = curvesScene->addPath(varList.at(i)->getPath(),
                                                       varList.at(i)->getPenStyle());
        pathList.erase(pathList.begin()+i);
        pathList.insert(pathList.begin()+i, path);
    }
}

//Slot to display/hide the graphics
void MainWindow::on_actionAddGraph_triggered()
{
    curvesView->setVisible(true);
}

//Slot for deleting Pair
void MainWindow::on_pair_delete(Pair* pair)
{
    int varNumber = varList.size();

    for(int i = 0; i < varNumber; i++){
        if(pair == varList.at(i))
        {
            curvesScene->removeItem(pathList.at(i));
            varList.erase(varList.begin()+i);
            pathList.erase(pathList.begin()+i);
            delete pair;
            return;
        }
    }
}
