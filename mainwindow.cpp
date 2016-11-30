#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    move(50, 50);

    serial = new QSerialPort(this);
    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readData()
{

}

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

void MainWindow::on_actionPort_settings_triggered()
{
    SerialSettings serialSettings(this, serial);
    serialSettings.exec();

}

void MainWindow::on_actionAdd_var_triggered()
{
    bool ok = 0;
    QString name = QInputDialog::getText(this, "New var", "Var name", QLineEdit::Normal, QString(), &ok);
    if(ok && !name.isEmpty()){
        Pair *pair = new Pair(ui->pairsLayout, name);
        pairList.push_back(pair);
    }
}

