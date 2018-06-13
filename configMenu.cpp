#include "configMenu.h"
#include "ui_configMenu.h"
#include <QDebug>
configMenu::configMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configMenu)
{
    ui->setupUi(this);
    ui->Dev1IPEdit->setText("192.168.0.1");
    QObject::connect(ui->Dev1CheckBox, &QCheckBox::clicked, [](){
    });
}

configMenu::~configMenu()
{
    delete ui;
}
