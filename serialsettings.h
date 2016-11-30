#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QDialog>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>

namespace Ui {
class SerialSettings;
}

class SerialSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SerialSettings(QWidget *parent = 0, QSerialPort *serialport = 0);
    ~SerialSettings();

    void updatePorts();

private slots:
    void on_updatePushButton_pressed();

    void on_buttonBox_accepted();

    void on_portComboBox_currentIndexChanged(int index);

    void on_baudrateComboBox_currentIndexChanged(int index);

private:
    Ui::SerialSettings *ui;

    QList<QSerialPortInfo> ports;
    QStringList portNames;
    QStringList baudrates;

    int portIndex;
    int baudrateIndex;

    QSerialPort *serial;

};

#endif // SERIALSETTINGS_H
