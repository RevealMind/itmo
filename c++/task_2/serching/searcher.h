#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QSet>

#include <indexing/indexer.h>

class Searcher : public QObject
{
    Q_OBJECT
public:
    Searcher(QString const &);
    bool process(Indexer const&);
private:
    QString substring;
    QSet<uint32_t> substringTrigrams;
    bool findSubstring(QString const &);
signals:

};

#endif // SEARCHER_H
