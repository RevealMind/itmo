#include "scanner.h"

#include <QtCore/QThread>
#include <QCryptographicHash>
#include <QDebug>

Scanner::Scanner (std::list<QString> const& dirs,
                std::map<option, bool>const& flags) :dirs(dirs), flags(flags) {
    qRegisterMetaType<std::list<QString>>("matches");

}

void Scanner::scan() {
    emit progress(0);
    std::map<size_t, std::list<QString>> sizeMap;
    for (auto i: dirs) {
        QDirIterator it(i, QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden,
                            flags.at(option::SubFolders) ?
                                    QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);
        while (it.hasNext()) {
            it.next();
            size_t size = it.fileInfo().size();
            sizeMap[size].push_back(it.filePath());
        }
        if (QThread::currentThread()->isInterruptionRequested()) {
            emit finished();
            return;
        }
    }

    size_t curProgressSize = 1;

    for (auto i: sizeMap) {
        if (i.second.size() == 1) {
            continue;
        }
        curProgressSize++;
        std::map<QString, std::list<QString>> hashMap;
        for (auto j: i.second) {            
            processFile(j, hashMap);
            if (QThread::currentThread()->isInterruptionRequested()) {
                emit finished();
                return;
            }
        }
        emit progress(100 * curProgressSize / sizeMap.size());
        for (auto j: hashMap) {
            if (j.second.size() > 1) {
                emit foundMatch(std::move(j.second));
            }
        }

        if (QThread::currentThread()->isInterruptionRequested()) {
            break;
        }
    }
    emit progress(100);
    emit finished();
}

void Scanner::processFile(QString const& filePath, std::map<QString, std::list<QString>>& hashMap) {
    QFile curFile(filePath);
    QString curHash = getHash(filePath);
    if (curHash == nullptr) {
        emit foundError(filePath);
        return;
    }
    hashMap[curHash].push_back(filePath);
}

QString Scanner::getHash(QString const& filePath) {
    QFile curFile(filePath);
    if (curFile.open(QFile::ReadOnly)) {
        QCryptographicHash hasher(QCryptographicHash::Sha256);
        if (hasher.addData(&curFile)) {
            return QString(hasher.result().toHex());
        } else {
            return nullptr;
        }
    }
    return nullptr;
}


