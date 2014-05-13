#ifndef EDITMSGDIALOG_H
#define EDITMSGDIALOG_H
#include <QDialog>
#include <QString>
#include <QStringList>
#include <vector>

#include "message.h"
#include "ui_editmsgdialo.h"

const QString defaultSteamDir = QString("C:/Program Files (x86)/Steam/SteamApps/common/dota 2 beta/dota/resource/dota_english.txt");

class EditMsgDialog : public QDialog, private Ui::EditMsgDialo{
    Q_OBJECT
public:
    EditMsgDialog(QWidget *parent = 0);
private slots:
    void openFile();
    void comboChanged(QString comboName);
    void lineEdited(QString lineContent);
    void saveFile();
private:
    void readFile(const QString& src);
    void allocateMessage();
    void removeQuote(QString& s);
    void addQuote(QString& s);
    void saveCondition();

    QString curDir;
    QStringList textData;
    QStringList lineData;

    std::vector<Message *> messageList;
};


#endif // EDITMSGDIALOG_H
