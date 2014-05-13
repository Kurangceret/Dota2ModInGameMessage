#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include <QString>

class Message : public QObject{
    Q_OBJECT
public:
    //Message(QObject *parent = 0) : QObject(parent), content("")
     // ,comboBoxName(""),dataName(""){ }

    Message(QObject *parent = 0, const QString &comboBoxName = "", const QString &dataName = "")
        :QObject(parent), content("")
    {
        this->comboBoxName = comboBoxName;
        this->dataName = dataName;
    }

    void setContent(const QString &newC){ content = newC; }
    QString getContent(){ return content; }

    QString getData(){ return dataName; }
    QString getCombo(){ return comboBoxName; }
private:
    QString content;    //the real text content
    QString comboBoxName;   //name in comboBox interface
    QString dataName;   //name in dota_english.txt
};


#endif // MESSAGE_H
