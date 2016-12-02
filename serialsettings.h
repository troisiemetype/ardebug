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
