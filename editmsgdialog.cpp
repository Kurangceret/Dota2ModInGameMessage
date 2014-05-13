#include <QtGui>
#include <iostream>
#include "editmsgdialog.h"
#include "namespace.h"



EditMsgDialog::EditMsgDialog(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);
    curDir = defaultSteamDir;
    connect(browseButton,SIGNAL(clicked()),this,SLOT(openFile()));
    connect(messageComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(comboChanged(QString)));
    connect(messageLineEdit,SIGNAL(textEdited(QString)),this,SLOT(lineEdited(QString)));
    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveFile()));
    setWindowTitle("Dota 2 Alpha Mod's Message");
    readFile(curDir);
}

void EditMsgDialog::openFile()
{
    QString name = QFileDialog::getOpenFileName(this,tr("Open file"),".");
    if(name.isNull())
        return;
    curDir = name;
    readFile(curDir);
}

void EditMsgDialog::readFile(const QString &src)
{
    QFile file(src);
    QFile filez(src);
    if(!file.open(QIODevice::ReadOnly)){
        std::cout << "Cannot open to Read " << std::endl;
    }
    if(!filez.open(QIODevice::ReadOnly))
        std::cout << "Cannot open to read/write " << std::endl;
    QFileInfo info(file);
    std::cout << info.absoluteFilePath().toStdString() << std::endl;

    QTextStream in(&file);
    QTextStream tmp(&filez);
    QString tempString;
    QString mString;
    textData.clear();   //clear the data, so previous text data is erased to prevent duplicate
    while(!in.atEnd()){ //get all text data one by one from dota_english.txt
        in >> tempString;
        textData << tempString;
    }
    lineData.clear();
    while(!tmp.atEnd()){    //get all text data line by line from dota_english.txt
        mString = tmp.readLine();
        lineData << mString;
    }
   allocateMessage();
}

void EditMsgDialog::allocateMessage()
{
    messageComboBox->clear();   //to assure no error
    //delete all previous object allocated
    for(int d = 0; d < messageList.size(); d++)
        delete messageList[d];

    messageList.clear();
    QString tempString;
    for(int i = 0; i < textData.size(); i++){
        for(int k = 0; k < contentName::dataSizes; k++){
            if(textData[i] == contentName::dataName[k]){    //ecounter the key word we wanted ?
                messageList.push_back(new Message(this,contentName::comboBoxName[k],
                                                  contentName::dataName[k]));
                //std::cout << textData[i].toStdString() << " ";/*<< " " << textData[i + 1].toStdString() << std::endl*/
                int j = i + 1;
                tempString = "";
                forever{
                    //std::cout << " " << textData[j].toStdString();


                    if(textData[j].endsWith(QChar('\"'))){
                        tempString.append(textData[j]);
                        break;
                    }
                    tempString.append(textData[j] + " ");
                    j++;

                }
                messageList[k]->setContent(tempString);
                messageComboBox->addItem(messageList[k]->getCombo());
                break;
            }
        }
    }
    saveCondition();
    //std::cout << std::endl;

}

void EditMsgDialog::comboChanged(QString comboName)
{
    for(int i = 0; i < messageList.size(); i++){
        if(messageList[i]->getCombo() == comboName){
            QString forCombo = messageList[i]->getContent();
            removeQuote(forCombo);
            messageLineEdit->setText(forCombo);
            break;
        }
    }
}

void EditMsgDialog::removeQuote(QString &s)
{
    s.remove(0,1);
    s.remove(s.size() - 1, 1);
}

void EditMsgDialog::addQuote(QString &s)
{
    s.prepend('\"');
    s.append('\"');
}

void EditMsgDialog::lineEdited(QString lineContent)
{
    for(int i = 0; i < messageList.size(); i++){
        if(messageComboBox->currentText() == messageList[i]->getCombo()){
            QString newContent = lineContent;
            addQuote(newContent);
            messageList[i]->setContent(newContent);
            break;
        }
    }
}

void EditMsgDialog::saveFile()
{

    QFile file(curDir);

    QTextStream in(&file);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        std::cout << "Cannot open to write" << std::endl;


    in.setCodec("UTF-16LE");
    in.setLocale(QLocale::English);
    in.setGenerateByteOrderMark(true);

    QString abc;    //used to store 1 line
    QStringList dem;    //will be use to spilt using "
    QStringList realPair;   //the list used to print the text to the file with customed text from GUI
    bool customData;
    for(int co = 0; co < lineData.size(); co++){
        customData = false;
        for(int sz = 0; sz < messageList.size(); sz++){
            if(lineData[co].contains(messageList[sz]->getData())){
                customData = true;
                realPair.clear();
                abc = lineData[co];
                dem = abc.split('\"');
                for(int i = 0; i < dem.size(); i++){
                    //check whether it has english letters or % indicator (eg...%s1)
                    if(dem[i].contains(QRegExp("[A-Z]")) || dem[i].contains(QChar('%'))){
                        realPair << dem[i];
                    }
                }
                realPair[0] = messageList[sz]->getData();
                realPair[1] = messageList[sz]->getContent();
                in << realPair[0] << " " << realPair[1] << "\n";
            }
        }
        if(!customData)
            in << lineData[co] << "\n";
    }

}

void EditMsgDialog::saveCondition()
{
    if(messageList.empty()){
        saveButton->setEnabled(false);
        messageLineEdit->setText("");
    }else{
        saveButton->setEnabled(true);
    }
}

//old save file
/*QFile file(curDir);
if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    std::cout << "Cannot open to Write " << std::endl;

QTextStream out(&file);

for(int i = 0; i < textData.size(); i++){
    out << textData[i] << " ";



    for(int k = 0; k < messageList.size(); k++){
        if(textData[i] == messageList[k]->getData()){   //if we found the data we wanted to replace the content
            out << messageList[k]->getContent() << " ";
            int j = i + 1;
            forever{    //increment j so that old data that textData was holding is gone.
                if(textData[j].endsWith(QChar('\"')))
                    break;

                j++;
            }
            i = j;  //then put i same pos as j to execute it, no need to add 1 because loop will increment i later

            break;
            //spacingCount += 2;


        }
    }


 }*/
