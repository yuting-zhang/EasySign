#ifndef CONFIGDATA_H
#define CONFIGDATA_H
#define DOCUMENTDIR QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/EasySign"

#include <map>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QStandardPaths>
#include <utility>

class ConfigData
{
public:
    ConfigData();
    void reportFileDamaged();
    QString get(QString);
    void put(QString,QString);
    void readConfig();
private:
    void initFile();

    std::map<QString,QString> config;
    std::pair<QString,QString> parse(const QString&) const;
};

#endif // CONFIGDATA_H
