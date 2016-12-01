#include "suppresspair.h"
#include "ui_suppresspair.h"

SuppressPair::SuppressPair(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SuppressPair)
{
    ui->setupUi(this);
}

SuppressPair::~SuppressPair()
{
    delete ui;
}

void SuppressPair::addLine()
{

}
