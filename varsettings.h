#ifndef VARSETTINGS_H
#define VARSETTINGS_H

#include <QDialog>

namespace Ui {
class VarSettings;
}

class VarSettings : public QDialog
{
    Q_OBJECT

public:
    explicit VarSettings(QWidget *parent = 0);
    ~VarSettings();

private:
    Ui::VarSettings *ui;
};

#endif // VARSETTINGS_H
