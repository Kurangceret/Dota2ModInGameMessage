#include "editmsgdialo.h"
#include "ui_editmsgdialo.h"

EditMsgDialo::EditMsgDialo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditMsgDialo)
{
    ui->setupUi(this);
}

EditMsgDialo::~EditMsgDialo()
{
    delete ui;
}
