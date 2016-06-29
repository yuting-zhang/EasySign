#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <map>
#include <QMediaPlaylist>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include "configdata.h"

class Dictionary
{
public:
    Dictionary(ConfigData*);
    ~Dictionary();
    bool generatePlaylist(QString, QMediaPlaylist&, bool);
    void ReloadConfig();
    void ResetDictionary();
private:
    std::map<QString,QString> dic;
    ConfigData* config;

};

#endif // DICTIONARY_H
