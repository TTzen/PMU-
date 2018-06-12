#include "mainScreen.h"
#include "ui_mainScreen.h"
#include <QMessageBox>
#include <QDebug>
mainScreen::mainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);
}

mainScreen::~mainScreen()
{
    delete ui;
}
