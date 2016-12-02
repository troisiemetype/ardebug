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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QDialog>
#include <QGraphicsPathItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QWidget>

#include <iostream>
#include <vector>

#include "dialog.h"
#include "graphview.h"
#include "pair.h"
#include "serialsettings.h"

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool readPair();

    QString getTrimString(char*);

public slots:

    void on_pair_delete(Pair*);

    void on_pair_update(Pair*);

private slots:

    void readData();

    void on_actionConnect_triggered(bool checked);

    void on_actionAdd_var_triggered();

    void on_actionPort_settings_triggered();

    void on_clearAllButton_clicked();

    void on_pauseAllButton_clicked(bool checked);

    void on_timer_timeout();

    void on_actionAddGraph_triggered();

private:

    Ui::MainWindow *ui;

    //Pointer to the serial object
    QSerialPort *serial;

    //Pointer table to the Pairs followed
    vector<Pair*> varList;
    //Pointer table to the graphs created
    vector<GraphView*> graphList;

    int timestamp;

};

#endif // MAINWINDOW_H
