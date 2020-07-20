#include "searcher.h"
#include <QDebug>
#include <QThread>

Searcher::Searcher(QString const & substiring) : substring(substiring) {}

bool Searcher::process(Indexer const & file) {
    int substringLength = substring.length();
    if (substringLength >= 3) {
        std::vector<uint8_t> symbols(substringLength);
        std::string subStringStd = substring.toUtf8().constData();

        for (size_t i = 0; i < substringLength; ++i) {
            symbols[i] = static_cast<uint8_t>(subStringStd[i]);
        }

        uint32_t trigram = 0 | (symbols[0] << 8) | symbols[1];
        for (size_t i = 2; i < substringLength; ++i) {
            trigram <<= 8;
            trigram |= symbols[i];
            substringTrigrams.insert(trigram & 0xFFFFFF);
        }
    }
    bool contains = true;

    for (auto it = substringTrigrams.begin(); it != substringTrigrams.end(); it++) {
        if (!std::binary_search(file.trigrams.begin(), file.trigrams.end(), *it))
            contains = false;
    }

    if ((contains || substringLength < 3) && findSubstring(file.getFilePath())) {
        return true;
    }

    return false;
}


bool Searcher::findSubstring(QString const &filePath) {

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QString("File %1 can't be opened").arg(filePath);
        return false;
    }

    while (!file.atEnd()) {
        QString q_line = file.read(4194304);
        if (q_line.indexOf(substring) >= 0)
            return true;
    }

    return false;
}
