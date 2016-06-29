#ifndef STUDYQUEUE_H
#define STUDYQUEUE_H
#include <QString>
#include <ctime>
#include <vector>
#include "configdata.h"
#include <map>
#include <QStringList>
#include <QTextStream>
#include <utility>

#define UNITCOUNT 7

class StudyItem
{
    friend class StudyQueue;
    friend QTextStream& operator<< (QTextStream&, const StudyItem&);
    friend QTextStream& operator>> (QTextStream&, StudyItem&);
    friend bool operator ==(const StudyItem&, const StudyItem&);
public:
    StudyItem();
    StudyItem(const QString&, const QString&);
    StudyItem(const QString&);
    QString getUnitID() const;
    QString getWord() const;
    void incLevel();
    void decLevel();
    void unchange();
private:
    QString word;
    int level;
    time_t next;
    QString unitID;
    static const std::vector<time_t> interval;
};

QTextStream& operator<< (QTextStream&, const StudyItem&);
QTextStream& operator>> (QTextStream&, StudyItem&);
bool operator ==(const StudyItem&, const StudyItem&);

class StudyQueue
{
public:
    StudyQueue(ConfigData*);
    void ReloadConfig();
    void ResetStudyQueue();
    void sort();
    void updateFiles();
    bool learningEmpty();
    std::vector<std::pair<QString,QString>> getUnits() const;
    QStringList* getLearning();
    StudyItem* getNext();
private:
    void initFile();
    const std::vector<QString> unitsName={"UNIT1","UNIT2","UNIT3","UNIT4","UNIT5","UNIT6","UNIT7"};
    std::vector<StudyItem> queue;
    std::vector<StudyItem> unlearned;
    std::map<QString,std::vector<QString>> units;
    ConfigData* config;
    QStringList learningUnits;    
};

#endif // STUDYQUEUE_H
