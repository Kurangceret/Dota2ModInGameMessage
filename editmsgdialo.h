#ifndef EDITMSGDIALO_H
#define EDITMSGDIALO_H

#include <QDialog>

namespace Ui {
class EditMsgDialo;
}

class EditMsgDialo : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditMsgDialo(QWidget *parent = 0);
    ~EditMsgDialo();
    
private:
    Ui::EditMsgDialo *ui;
};

#endif // EDITMSGDIALO_H
