#include "studyqueue.h"
#include <QFile>
#include <algorithm>
#include <QDebug>
#include <ctime>


const std::vector<time_t> StudyItem::interval={300,300,1800,43200,86400,172800,345600,604800,1296000,2592000,5184000,15552000,31104000,46656000,93312000};

StudyItem::StudyItem():level(0),next(0)
{
}

StudyItem::StudyItem(const QString& val): word(val), level(0),next(0)
{
}


StudyItem::StudyItem(const QString& val, const QString & parent): word(val), level(0),next(0),unitID(parent)
{
}

QTextStream& operator<< (QTextStream& os, const StudyItem& item)
{
    os<< item.word<< " "<< item.level<< " "<< item.next<< " "<< item.unitID;
    return os;
}
QTextStream& operator>> (QTextStream& is, StudyItem& item)
{
    is>> item.word>>item.level>> item.next>> item.unitID;
    return is;
}

bool operator== (const StudyItem& lhs, const StudyItem& rhs)
{
    return lhs.word == rhs.word;
}

QString StudyItem::getUnitID() const
{
    return unitID;
}

QString StudyItem::getWord() const
{
    return word;
}

void StudyItem::incLevel()
{
    if (level==0)
    {
        level+=2;
        next=time(0)+interval[level];
    }
    else
    {
        ++level;
        next=time(0)+interval[level];
    }
}

void StudyItem::decLevel()
{
    if (level==0)
    {
        ++level;
        next=time(0)+interval[level];
    }
    else
        if (level==1)
        {
            next=time(0)+interval[level];
        }
        else
        {
            --level;
            next=time(0)+interval[level];
        }
}

void StudyItem::unchange()
{
    if (level==0)
        ++level;
    next=time(0)+30;
}




StudyQueue::StudyQueue(ConfigData* data):
    config(data)
{
    if (!QFile(DOCUMENTDIR+"/queue.es").exists() || !QFile(DOCUMENTDIR+"/unlearned.es").exists())
        initFile();
    ReloadConfig();
}

void StudyQueue::ReloadConfig()
{
    learningUnits=config->get("LEARN").split(' ',QString::SkipEmptyParts);
    for (const auto& it: learningUnits)
        if (std::find(unitsName.begin(),unitsName.begin()+UNITCOUNT,it)==unitsName.begin()+UNITCOUNT)
        {
            config->reportFileDamaged();
            ReloadConfig();
            return;
        }
   ResetStudyQueue();
}

void StudyQueue::initFile()
{
    QFile FQueue(DOCUMENTDIR+"/queue.es");
    QFile FUnlearned(DOCUMENTDIR+"/unlearned.es");
    FQueue.open(QIODevice::ReadOnly | QIODevice::Text);
    FUnlearned.open(QIODevice::ReadOnly | QIODevice::Text);
}

void StudyQueue::ResetStudyQueue()
{
    queue.clear();
    unlearned.clear();
    units.clear();
    for (size_t i=0; i!=UNITCOUNT; ++i)
    {
        QFile fin(QCoreApplication::applicationDirPath()+"/data/units/"+unitsName[i]+".es");
        fin.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&fin);
        QString word;
        while (!in.atEnd())
        {
            in>> word;
            units[unitsName[i]].push_back(word);
        }
    }
    QFile FQueue(DOCUMENTDIR+"/queue.es");
    QFile FUnlearned(DOCUMENTDIR+"/unlearned.es");
    FQueue.open(QIODevice::ReadOnly | QIODevice::Text);
    FUnlearned.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream QueueIn(&FQueue);
    QTextStream UnlearnedIn(&FUnlearned);
    StudyItem item;
    while (!QueueIn.atEnd())
    {
        QueueIn>> item;
        queue.push_back(item);
    }
    while (!UnlearnedIn.atEnd())
    {
        UnlearnedIn>> item;
        unlearned.push_back(item);
    }
    FQueue.close();
    FUnlearned.close();
    auto it=unlearned.begin();
    while (it!=unlearned.end())
        if (std::find(learningUnits.begin(),learningUnits.end(),(*it).getUnitID())==learningUnits.end())
            it=unlearned.erase(it);
        else
            ++it;
    for (auto& i: learningUnits)
        for (auto j=units[i].begin()+1; j!=units[i].end(); ++j)
            if (std::find(unlearned.begin(),unlearned.end(),StudyItem(*j))==unlearned.end() && std::find(queue.begin(),queue.end(),StudyItem(*j))==queue.end())
                unlearned.push_back(StudyItem(*j,i));
    sort();
    updateFiles();
}

void StudyQueue::updateFiles()
{
    QFile FQueue(DOCUMENTDIR+"/queue.es");
    QFile FUnlearned(DOCUMENTDIR+"/unlearned.es");
    FQueue.open(QIODevice::WriteOnly | QIODevice::Text);
    FUnlearned.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream QueueOut(&FQueue);
    QTextStream UnlearnedOut(&FUnlearned);
    for (decltype(queue.size()) it=0; it+1<queue.size();++ it)
        QueueOut<< queue[it]<< "\n";
    if (queue.size()>1)
        QueueOut<< queue.back();
    for (decltype(unlearned.size()) it=0; it+1 <unlearned.size();++ it)
        UnlearnedOut<< unlearned[it]<< "\n";
    if (unlearned.size()>1)
        UnlearnedOut<< unlearned.back();
}

void StudyQueue::sort()
{
    if (!unlearned.empty() && unlearned[0].level!=0)
    {
        StudyItem item=unlearned[0];
        unlearned.erase(unlearned.begin());
        queue.push_back(item);
    }
    std::sort(queue.begin(),queue.end(),[](const StudyItem& lhs, const StudyItem& rhs){return lhs.next<rhs.next;});
    auto curr_t=time(0);
    auto it=queue.begin();
    while (it!=queue.end() && it->next <=curr_t)
        ++it;
    std::random_shuffle(queue.begin(),it);
}

StudyItem* StudyQueue::getNext()
{
    auto item=queue.begin();
    while (item!=queue.end() && std::find(learningUnits.begin(),learningUnits.end(),item->getUnitID())==learningUnits.end())
        ++item;
    if (item!=queue.end() &&  item->next<time(0))
        return &(*item);
    else
        if (!unlearned.empty())
            return &unlearned[0];
        else
            return nullptr;
}

bool StudyQueue::learningEmpty()
{
    if (learningUnits.empty())
        return true;
    else
        return false;
}

std::vector<std::pair<QString,QString>> StudyQueue::getUnits() const
{
    std::vector<std::pair<QString,QString>> ret;
    for (const auto& it: units)
        ret.push_back({it.first,it.second[0]});
    return ret;
}

QStringList* StudyQueue::getLearning()
{
    return &learningUnits;
}
