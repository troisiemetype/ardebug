#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QMainWindow>
#include <QSerialPort>
#include <QString>

#include <iostream>
#include <vector>

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

private slots:

    void readData();

    void on_actionConnect_triggered(bool checked);

    void on_actionAdd_var_triggered();

    void on_actionPort_settings_triggered();

private:
    Ui::MainWindow *ui;

    QSerialPort *serial;

    vector<Pair*> pairList;

};

#endif // MAINWINDOW_H
