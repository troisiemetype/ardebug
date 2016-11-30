#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMainWindow>
#include <QSerialPort>
#include <QString>
#include <QStringList>
#include <QWidget>

#include <iostream>
#include <vector>

#include "dialog.h"
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

private slots:

    void readData();

    void on_actionConnect_triggered(bool checked);

    void on_actionAdd_var_triggered();

    void on_actionPort_settings_triggered();

    void on_actionRemove_var_triggered();

private:
    Ui::MainWindow *ui;

    QSerialPort *serial;

    vector<Pair*> varList;

};

#endif // MAINWINDOW_H
