#ifndef ATMCHANGE_H
#define ATMCHANGE_H

#include <QDialog>

namespace Ui {
class atmchange;
}

class atmchange : public QDialog
{
    Q_OBJECT

public:
    explicit atmchange(QWidget *parent = 0);
    ~atmchange();

private:
    Ui::atmchange *ui;
};

#endif // ATMCHANGE_H
