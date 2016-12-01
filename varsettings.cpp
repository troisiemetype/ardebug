#include "varsettings.h"
#include "ui_varsettings.h"

VarSettings::VarSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VarSettings)
{
    ui->setupUi(this);
}

VarSettings::~VarSettings()
{
    delete ui;
}
