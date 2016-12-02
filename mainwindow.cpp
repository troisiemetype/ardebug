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

    timestamp = 0;

    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    timer->start(1);
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
    QString name = getTrimString(data);

    //Verifies if the var received match a var that is watched
    for(int i = 0; i < varList.size(); i++){
        //if yes, update value
        if(name == varList.at(i)->getName()){
            serial->readLine(data, 64);
            QString value = getTrimString(data);
            varList.at(i)->update(value, timestamp);
            return true;
        }
    }
    return false;

}

//Trim the trailing chars \r \n added by Arduino Serial.prinln()
QString MainWindow::getTrimString(char *data)
{
    QString name = QString(data);
    return name.remove(name.size()-2, 2);
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
//TODO: add Pair.clear() when open
void MainWindow::on_actionConnect_triggered(bool checked)
{
    if(checked){
        if(serial->open(QIODevice::ReadOnly))
        {
            timestamp = 0;
            for(int i = 0; i < varList.size(); i++){
                varList.at(i)->clear();
            }
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
//TODO: use the var settings window instead
void MainWindow::on_actionAdd_var_triggered()
{
    bool ok = 0;
    //get a name for an input box
    QString name = QInputDialog::getText(this, "New var", "Var name", QLineEdit::Normal, QString(), &ok);
    //Create a pair if name has been set, and ok clicked
    if(ok && !name.isEmpty()){
        Pair *pair = new Pair(this, ui->pairsLayout, name);
        varList.push_back(pair);
        pair->setIndex(varList.size());
    }
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

//slot for timer: increment timestamp
//TODO: create a class to handle graphics, put the timer in it
void MainWindow::on_timer_timeout()
{
    if(!serial->isOpen()){
        return;
    }

    timestamp++;
}

//Slot to display a new graphic window
void MainWindow::on_actionAddGraph_triggered()
{
    GraphView *graphView = new GraphView(this, &varList);
    graphList.push_back(graphView);
    graphView->show();
}

//Slot for deleting Pair. Defined at Pair creation
void MainWindow::on_pair_delete(Pair* pair)
{
    int varNumber = varList.size();

    for(int i = 0; i < varNumber; i++){
        if(pair == varList.at(i))
        {
            varList.erase(varList.begin()+i);
            delete pair;
            return;
        }
    }
}

void MainWindow::on_pair_update(Pair* pair)
{

}
