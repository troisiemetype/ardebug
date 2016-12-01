#ifndef PAIR_H
#define PAIR_H

#include <QGraphicsScene>
#include <QGraphicsItem>
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

    void update(int, int);
    void updateGui();
    void clear();

    void createWidget();

    QString getName();
    int getValue();
    QLine getCurve(int);

    QPen getPenStyle();

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

    int prevX;
    int prevY;

    int valuesSize;

    QPen *penStyle;

    QLabel *nameLabel;
    QLineEdit *valueLabel;
    QLineEdit *minLabel;
    QLineEdit *maxLabel;

    QPushButton *pauseButton;
    QPushButton *clearButton;
    QPushButton *optionButton;

public slots:

    void on_pauseButton_clicked(bool);

    void on_clearButton_clicked();

protected slots:

    void on_optionButton_clicked();

};

#endif // PAIR_H
