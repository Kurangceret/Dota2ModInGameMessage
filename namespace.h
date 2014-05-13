#ifndef NAMESPACE_H
#define NAMESPACE_H
#include <QString>

namespace contentName{
    //must be in order with dataName[]
    const QString comboBoxName[] = { QString("Player Killed")
                                     , QString("Player Denied"), QString("Rampage Effect Text") };
    //must be in order with comboBoxName[]
    const QString dataName[] = { QString("\"DOTA_Chat_PlayerKilled\"")
                                 , QString("\"DOTA_Chat_PlayerDenied\""),QString("\"DOTA_Chat_Rampage\"") };
    int comboSizes = sizeof(comboBoxName) / sizeof(*comboBoxName);
    int dataSizes = sizeof(dataName) / sizeof(*dataName);
}
#endif // NAMESPACE_H
