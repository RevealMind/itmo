#ifndef INDEXERTHREAD_H
#define INDEXERTHREAD_H

#include <QObject>
#include "indexer.h"

class IndexerThread : public QObject
{
    Q_OBJECT
public:
    IndexerThread(QString const&);

private:
    QString const directory;
    std::vector<Indexer> files;

signals:
    void finished();
    void updateIndexerProgressMaxValue(int);
    void increaseIndexerProgressBar();
    void sendTextFiles(std::vector<Indexer>);
    void foundFile(Indexer);
public slots:
    void proccess();
};

#endif // INDEXERTHREAD_H
