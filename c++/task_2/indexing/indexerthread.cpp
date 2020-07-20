#include "indexerthread.h"

#include <QDirIterator>
#include <QThread>

IndexerThread::IndexerThread(QString const& directory) : directory(directory) {}

void IndexerThread::proccess() {
    files.clear();
    QDirIterator it(QDir::currentPath(), QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot,
                      QDirIterator::Subdirectories);
    while (it.hasNext()) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            emit finished();
            return;
        }
        it.next();
        files.push_back(Indexer(it.filePath()));
    }

    emit updateIndexerProgressMaxValue(files.size());

    for (auto &file: files) {
        file.process();
        if (QThread::currentThread()->isInterruptionRequested()) {
            emit finished();
            return;
        }

        if (file.isText()) {
            emit foundFile(file);
        }

        emit increaseIndexerProgressBar();
    }
    emit finished();
    return;
}
