#ifndef PAIR_H
#define PAIR_H

#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include <iostream>
#include <vector>

using namespace std;
class Pair : public QObject
{
    Q_OBJECT

public:
    Pair();
    ~Pair();

    Pair(QGridLayout*, QString);

    void update(int);
    void updateGui();
    void clear();

    void createWidget();

    QString getName();

private:

//    QWidget *parent;
    QGridLayout *parentLayout;

    bool firstTime;
    bool pause;
    QString name;
    int value;
    int minValue;
    int maxValue;
    vector<int> values;

    int valuesSize;

    QLabel *nameLabel;
    QLineEdit *valueLabel;
    QLineEdit *minLabel;
    QLineEdit *maxLabel;

    QPushButton *pauseButton;
    QPushButton *clearButton;
    QPushButton *optionButton;

private slots:

    void on_pauseButton_clicked(bool);

    void on_clearButton_pressed();

    void on_optionButton_pressed();

};

#endif // PAIR_H
