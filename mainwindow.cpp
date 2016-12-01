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
    curvesView = new QGraphicsView(curvesScene);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    timer->start(100);
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
            varList.at(i)->update(value.toInt(), currentX);
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
        curvesScene->addLine(varList.at(i)->getCurve(currentX),
                             varList.at(i)->getPenStyle());
    }
}

void MainWindow::on_actionShow_graph_triggered(bool checked)
{
    curvesView->setVisible(checked);
}
