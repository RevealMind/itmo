#include "indexer.h"

#include <qtextcodec.h>
#include <QDebug>
#include <QFileInfo>
#include <fstream>
#include <QThread>

Indexer::Indexer() : isIndexing(false), isOk(false) {}

Indexer::Indexer(const QString &filePath) : isIndexing(false), isOk(false),
    filePath(filePath), fileInfo(QFileInfo(filePath)) {}

Indexer::~Indexer() {
    trigrams.clear();
}

void Indexer::process() {

    QFile file(filePath);
       if (!file.open(QFile::ReadOnly)) {
           printError(QString("File %1 can't be opened").arg(fileInfo.fileName()));
           return;
       }
       const int BUFFER_SIZE = 1 << 18;
       const size_t MAXIMUM = 1 << 18;

       QTextStream stream(&file);
       QString buffer = stream.read(BUFFER_SIZE);
       if (buffer.size() < 3) {
           return;
       }

    //-----------------------------------------------------
    isIndexing = true;
    if (fileInfo.size() > MAX_FILE_SIZE) {
        printError(QString("Too large file %1").arg(fileInfo.fileName()));
        return;
    }

    std::ifstream in(filePath.toStdString());
    QSet <uint32_t> trigramsSet;
    //std::string line;


    while (buffer.size() >= 3) {
        if (QThread::currentThread()->isInterruptionRequested()) break;

        auto line_length = buffer.length();


        makeTrigramsSet(trigramsSet, buffer.toStdString(), line_length);


        if (trigramsSet.size() > MAX_TRIGRAMS_AMOUNT) {
            printError(QString("%1 contains too many trigrams").arg(fileInfo.fileName()));
            return;
        }
        buffer = stream.read(BUFFER_SIZE);
    }

    trigrams.clear();
    std::move(trigramsSet.begin(), trigramsSet.end(), std::back_inserter(trigrams));
    std::sort(trigrams.begin(), trigrams.end());
    isOk = true;
}

void Indexer::makeTrigramsSet(QSet <uint32_t> &trigramsSet, std::string const &line, size_t length) {
    auto std_line = line;
    uint8_t symbols[length];

    for (size_t i = 0; i < length; ++i) {
        symbols[i] = static_cast<uint8_t>(std_line[i]);
    }

    uint32_t trigram = 0 | (symbols[0] << 8) | symbols[1];
    for (size_t i = 2; i < length; ++i) {
        trigram <<= 8;
        trigram |= symbols[i];
        trigramsSet.insert(trigram & 0xFFFFFF);
    }
}

void Indexer::printError(const QString &error) {
    isOk = false;
    qDebug() << error;
}

bool Indexer::isText() const {
    return isIndexing && isOk;
}

QString Indexer::getFileName() const {
    return fileInfo.fileName();
}

QString Indexer::getFilePath() const {
    return filePath;
}
