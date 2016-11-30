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
