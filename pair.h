#ifndef PAIR_H
#define PAIR_H

#include <QGridLayout>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include <vector>

using namespace std;
class Pair
{
public:
    Pair();
    ~Pair();

    Pair(QGridLayout*, QString);

    void update();

    void createWidget();

private:

    QGridLayout *parentLayout;

    QString name;
    int value;
    int minValue;
    int maxValue;
    vector<int> values;

    QLabel *nameLabel;
    QLabel *valueLabel;
    QLabel *minLabel;
    QLabel *maxLabel;

    QPushButton *clearButton;
    QPushButton *optionButton;

};

#endif // PAIR_H
