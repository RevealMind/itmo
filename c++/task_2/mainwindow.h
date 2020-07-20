#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "indexing/indexerthread.h"
#include "indexing/indexerprogressdialog.h"
#include "serching/searcher.h"
#include "util/list.h"

#include <QMainWindow>
#include <QAction>
#include <QFileSystemWatcher>
#include <QListWidget>
#include <QFutureWatcher>

#include <QFileSystemWatcher>
#include <QMainWindow>
#include <QDir>
#include <memory>
#include <QDirIterator>
#include <QTreeWidgetItem>
#include <QCommonStyle>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDateTime>
#include <QFileSystemModel>
#include <QCryptographicHash>
#include <QIODevice>
#include <QWidgetItem>
#include <QMap>
#include <QTreeWidget>
#include <QKeyEvent>
#include <vector>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <QTimer>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static const qint64 MAX_FILE_SIZE = 10e6;

private:
    Ui::MainWindow *ui;
    QFileSystemWatcher systemWatcher;
    QThread *workThread = nullptr;
    std::vector<Indexer> textFiles;
    QFutureWatcher<void>* workSearcher;

    std::list<int> substringPostions;
    std::list<int>::iterator curSubstringPosition;

    bool stopSearch = false;

    void startIndexing();
    void showFile(QString const&);
    void findSubstring();
    void changeBackGroundColor(int, int, QColor);

protected:
    void keyPressEvent(QKeyEvent *);

public slots:
    void selectDir();
    void openSelectedFile(QListWidgetItem* );
    void fileChanged(const QString &path);
    void changeDisable();
    void substringChanged();
    void addToWatching(Indexer);
    void indexationFinished();


private slots:
    void on_actionExit_triggered();

    void on_prevButton_clicked();
    void on_nextButton_clicked();
};

#endif // MAINWINDOW_H
