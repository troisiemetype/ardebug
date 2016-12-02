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

#ifndef SUPPRESSPAIR_H
#define SUPPRESSPAIR_H

#include <QDialog>

namespace Ui {
class SuppressPair;
}

class SuppressPair : public QDialog
{
    Q_OBJECT

public:
    explicit SuppressPair(QWidget *parent = 0);
    ~SuppressPair();

    void addLine();

private:
    Ui::SuppressPair *ui;
};

#endif // SUPPRESSPAIR_H
