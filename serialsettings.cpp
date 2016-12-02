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

#include "serialsettings.h"
#include "ui_serialsettings.h"

SerialSettings::SerialSettings(QWidget *parent, QSerialPort *serialport) :
    QDialog(parent),
    ui(new Ui::SerialSettings)
{
    ui->setupUi(this);

    serial = serialport;

    baudrates << "115200" << "57600" << "38400" << "19200" << "9600" << "4800" << "2400" << "1200" ;

    ui->baudrateComboBox->addItems(baudrates);
    updatePorts();

}

SerialSettings::~SerialSettings()
{
    delete ui;
}

void SerialSettings::updatePorts()
{
    ports = QSerialPortInfo::availablePorts();

    int listSize = ports.size();

    for (int i = 0; i < listSize; i++){
        portNames << ports.value(i).portName();
    }
    ui->portComboBox->clear();
    ui->portComboBox->addItems(portNames);

}

void SerialSettings::on_updatePushButton_pressed()
{
    updatePorts();
}

void SerialSettings::on_buttonBox_accepted()
{
    serial->close();
    serial->setPortName(ports.value(portIndex).portName());
    serial->setBaudRate(baudrates.value(baudrateIndex).toInt());
}

void SerialSettings::on_portComboBox_currentIndexChanged(int index)
{
    portIndex = index;
}

void SerialSettings::on_baudrateComboBox_currentIndexChanged(int index)
{
    baudrateIndex = index;
}
