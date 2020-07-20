#ifndef INDEXER_H
#define INDEXER_H

#include <QFileInfo>
#include <QString>
#include <vector>


class Indexer
{
public:
    static const qint64 MAX_TRIGRAMS_AMOUNT = 20000;
    static const qint64 MAX_LINE_LENGTH = 2000;
    static const qint64 MAX_FILE_SIZE = 1 << 30;

    Indexer();
    Indexer(QString const &);
    ~Indexer();

    void process();
    bool isText() const;
    QString getFileName() const;
    QString getFilePath() const;

    std::vector<uint32_t> trigrams;

private:
    bool isIndexing;
    bool isOk;
    QString filePath;
    QFileInfo fileInfo;

    void makeTrigramsSet(QSet<uint32_t> &, std::string const&, size_t);
    void printError(QString const &);


};

#endif // INDEXER_H
