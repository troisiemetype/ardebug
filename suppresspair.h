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
