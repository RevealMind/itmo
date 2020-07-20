#ifndef SCANER_H
#define SCANER_H
#include "option.h"

#include <QString>
#include <QObject>
#include <QFlags>
#include <QDir>
#include <QDirIterator>

#include <map>
#include <list>
#include <vector>

class Scanner : public QObject
{
    Q_OBJECT
public:
    Scanner (std::list<QString> const& dirs,
            std::map<option, bool> const& flags);

signals:
        void foundMatch(std::list<QString> const& match);
        void foundError(QString const& filePath);
        void progress(int progress);
        void finished();
public slots:
        void scan();

private:
    void processFile(QString const& file_path, std::map<QString, std::list<QString>>& hashes);
    QString getHash(QString const& file_name);
    std::list<QString> dirs;
    std::map<option, bool> flags;

};

#endif // SCANER_H
