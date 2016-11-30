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

bool MainWindow::readPair()
{
    char *data = new char();
    serial->readLine(data, 64);
    QString name = QString(data);

    name.remove(name.size()-2, 2);

    for(int i = 0; i < varList.size(); i++){

        if(name == varList.at(i)->getName()){
            serial->readLine(data, 64);
            QString value = QString(data);
            varList.at(i)->update(value.toInt());
            return true;
        }
    }
    return false;

}

void MainWindow::readData()
{
    if(varList.size() == 0)
    {
        serial->clear(QSerialPort::Input);
        return;
    }
    readPair();
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
        varList.push_back(pair);
//        QObject::connect(pair->clearButton, SIGNAL(pressed()), pair, SLOT(on_clearButton_pressed()));
    }
}


void MainWindow::on_actionRemove_var_triggered()
{
    int varNumber = varList.size();

    if(varNumber == 0)
    {
        return;
    }

    Dialog varListDialog(this);

    QGridLayout *layout = new QGridLayout;

    for(int i = 0; i < varNumber; i++){

        QCheckBox *check = new QCheckBox();
        layout->addWidget(check, i, 0);

        QLabel *name = new QLabel(varList.at(i)->getName());
        layout->addWidget(name, i, 1);
    }

    varListDialog.setLayout(layout);

    varListDialog.exec();
}
