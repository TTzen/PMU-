#ifndef CONFIGMENU_H
#define CONFIGMENU_H

#include <QDialog>

namespace Ui {
class configMenu;
}

class configMenu : public QDialog
{
    Q_OBJECT

public:
    explicit configMenu(QWidget *parent = 0);
    ~configMenu();

private:
    Ui::configMenu *ui;
};

#endif // CONFIGMENU_H
