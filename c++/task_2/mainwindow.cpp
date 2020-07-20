#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <map>
#include <vector>
#include <set>
#include <functional>
#include <cstdint>
#include <algorithm>
#include <unordered_map>
#include <QTextCursor>
#include <locale>
#include <codecvt>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    workSearcher(new QFutureWatcher<void>(this))
{
    ui->setupUi(this);
    ui->verticalWidget->hide();
    connect(ui->actionOpen_dirictory, &QAction::triggered, this, &MainWindow::selectDir);
    connect(ui->filesWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::openSelectedFile);
    connect(&systemWatcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::fileChanged);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::substringChanged);

    ui->filesWidget->setStyleSheet("QListWidget { color: black ; background-color: white }" );
    ui->lineEdit->setStyleSheet("QLineEdit  { color: black ; background-color: white }");
    ui->lineEdit->setDisabled(true);

    QCommonStyle style;
    ui->prevButton->setIcon(style.standardIcon(QCommonStyle::SP_ArrowUp));
    ui->nextButton->setIcon(style.standardIcon(QCommonStyle::SP_ArrowDown));
    ui->actionOpen_dirictory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCloseButton));
    ui->textEdit->setFont(QFont(QStringLiteral("A Font Supporting Emoji")));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select directory", QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        ui->statusBar->showMessage(QString("Selected dir: %1").arg(dir));
        QDir::setCurrent(dir);
        MainWindow::startIndexing();
    } else {
        QMessageBox::information(this, "Warning", "Select directory.",
                                 QMessageBox::Ok);
    }
    return;
}

void MainWindow::startIndexing() {
    textFiles.clear();
    ui->filesWidget->clear();
    ui->textEdit->clear();
    ui->verticalWidget->hide();
    ui->lineEdit->clear();
    ui->lineEdit->setDisabled(true);

    if (!systemWatcher.directories().isEmpty())
        systemWatcher.removePaths(systemWatcher.directories());

    if (!systemWatcher.files().isEmpty())
        systemWatcher.removePaths(systemWatcher.files());

    systemWatcher.addPath(QDir::currentPath());

    IndexerThread* indexerThread = new IndexerThread(QDir::currentPath());
    workThread = new QThread();
    indexerThread->moveToThread(workThread);
    IndexerProgressDialog* progressDialog = new IndexerProgressDialog(workThread);

    connect(workThread, &QThread::started, this, &MainWindow::changeDisable);
    connect(workThread, &QThread::started, progressDialog, &QDialog::open);
    connect(workThread, &QThread::started, indexerThread, &IndexerThread::proccess);


    qRegisterMetaType <Indexer> ("Indexer");
    connect(indexerThread, &IndexerThread::updateIndexerProgressMaxValue, progressDialog, &IndexerProgressDialog::setRange);
    connect(indexerThread, &IndexerThread::increaseIndexerProgressBar, progressDialog, &IndexerProgressDialog::update);
    connect(indexerThread, &IndexerThread::foundFile, this, &MainWindow::addToWatching);

    connect(indexerThread, &IndexerThread::finished, progressDialog, &IndexerProgressDialog::close);
    connect(indexerThread, &IndexerThread::finished, this, &MainWindow::indexationFinished);
    connect(indexerThread, &IndexerThread::finished, workThread, &QThread::quit);
    connect(indexerThread, &IndexerThread::finished, indexerThread, &IndexerThread::deleteLater);

    connect(workThread, &QThread::finished, progressDialog, &QDialog::deleteLater);
    connect(workThread, &QThread::finished, workThread, &QThread::deleteLater);
    connect(workThread, &QThread::finished, this, &MainWindow::changeDisable);

    workThread->start();
}

void MainWindow::addToWatching(Indexer file) {
    textFiles.push_back(file);
    systemWatcher.addPath(file.getFilePath());
    showFile(file.getFilePath());

}

void MainWindow::indexationFinished() {
    if (textFiles.empty()) {
        QMessageBox::information(this, "Information", "Text files not found", QMessageBox::Ok);
        return;
    }
}

void MainWindow::openSelectedFile(QListWidgetItem* item) {
    if (ui->lineEdit->text().isEmpty()) {
        return;
    }
    QFile file(item->text());

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Warning", QString("File %1 can't be opened").arg(file.fileName()),
                                 QMessageBox::Ok);
        return;
    }
    if (file.size() > MAX_FILE_SIZE) {
        QMessageBox::information(this, "Warning", QString("File %1 too large for opening").arg(file.fileName()),
                                 QMessageBox::Ok);
    } else {
        ui->verticalWidget->show();
        ui->textEdit->clear();
        ui->textEdit->setPlainText(file.readAll());
        ui->textEdit->setTextBackgroundColor(Qt::GlobalColor::white);
        substringPostions.clear();

        std::u16string text = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(ui->textEdit->toPlainText().toStdString().data());
        std::u16string substring  = std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.from_bytes(ui->lineEdit->text().toStdString().data());

        auto it = text.begin();
        int count = 0;

        while ((it = std::search(it, text.end(),
                                 std::boyer_moore_horspool_searcher(
                                     substring.begin(), substring.end()))) != text.end()) {

            count++;
            substringPostions.push_back((it - text.begin()));

            changeBackGroundColor((it - text.begin()),
                                  (it - text.begin()) + ui->lineEdit->text().size(),
                                  QColor(144, 238, 144));
            it++;

        }

        curSubstringPosition = substringPostions.begin();

        changeBackGroundColor(*curSubstringPosition,
                              *curSubstringPosition + ui->lineEdit->text().size(),
                              QColor(255, 185, 64));


        ui->fileNameLable->setText(QString("Open: %1").arg(item->text()));
        ui->infoLabel->setText(QString("%1 matches was found").arg(count));
        ui->posLabel->setText(QString::number(1));
        ui->totalLabel->setText(QString("/ %1").arg(count));
    }
    return;
}

void MainWindow::fileChanged(const QString &path) {
    if (workSearcher->isRunning()) {
        stopSearch = true;
        workSearcher->waitForFinished();
    }

    ui->lineEdit->setText("");
    ui->verticalWidget->setHidden(true);
    ui->filesWidget->clear();
    for (auto it = textFiles.begin(); it != textFiles.end(); it++) {
        if (it->getFilePath() == path) {
            textFiles.erase(it--);
        }
    }

    Indexer indexer(path);
    indexer.process();
    if (indexer.isText())
        textFiles.push_back(indexer);


    for (auto it = textFiles.begin(); it != textFiles.end(); it++) {
        ui->filesWidget->sortItems();
        ui->filesWidget->addItem(it->getFilePath());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape :
            ui->verticalWidget->hide();
            ui->statusBar->showMessage(QString("Selected dir: %1").arg(QDir::currentPath()));
            break;
    }
}

void MainWindow::changeDisable() {
    bool state = ui->actionOpen_dirictory->isEnabled();
    ui->lineEdit->setDisabled(state);
    ui->actionOpen_dirictory->setDisabled(state);
}

void MainWindow::substringChanged() {


    ui->verticalWidget->setHidden(true);
    if (workSearcher->isRunning()) {
        stopSearch = true;
        workSearcher->waitForFinished();
    }

    if (ui->lineEdit->text().size() == 0) {
        ui->filesWidget->clear();
        for (auto it = textFiles.begin(); it != textFiles.end(); it++) {
            ui->filesWidget->addItem(it->getFilePath());
        }
        return;
    }

    ui->filesWidget->clear();
    workSearcher->setFuture(QtConcurrent::run(this, &MainWindow::findSubstring));
}

void MainWindow::findSubstring() {
    QString substring = ui->lineEdit->text();
    Searcher searcher(substring);
    for (auto it = textFiles.begin(); it != textFiles.end(); it++) {
        if (stopSearch) {
            stopSearch = false;
            break;
        }
        if(searcher.process(*it)) {
            showFile(it->getFilePath());
        }
    }
}

void MainWindow::showFile(const QString & filePath) {
     ui->filesWidget->addItem(filePath);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_nextButton_clicked()
{
     if (substringPostions.empty())
        return;

    changeBackGroundColor(*curSubstringPosition,
                          *curSubstringPosition + ui->lineEdit->text().size(),
                          QColor(144, 238, 144));

     int pos = ui->posLabel->text().toInt() + 1;
     if (++curSubstringPosition == substringPostions.end()){
        ++curSubstringPosition;
        pos = 1;
     }

     changeBackGroundColor(*curSubstringPosition,
                           *curSubstringPosition + ui->lineEdit->text().size(),
                           QColor(255, 185, 64));


     ui->posLabel->setText(QString::number(pos));
}

void MainWindow::on_prevButton_clicked()
{
    if (substringPostions.empty())
       return;

    changeBackGroundColor(*curSubstringPosition,
                          *curSubstringPosition + ui->lineEdit->text().size(),
                          QColor(144, 238, 144));

    int pos = ui->posLabel->text().toInt() - 1;

    if (--curSubstringPosition == substringPostions.end()) {
       curSubstringPosition--;
       pos = substringPostions.size();
    }

    changeBackGroundColor(*curSubstringPosition,
                          *curSubstringPosition + ui->lineEdit->text().size(),
                          QColor(255, 185, 64));

    ui->posLabel->setText(QString::number(pos));
}

void MainWindow::changeBackGroundColor(int begin, int end, QColor color) {
    QTextCursor cursor(ui->textEdit->document());
    QTextCharFormat charFormat;
    charFormat.setBackground(color);
    cursor.setPosition(begin, QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(cursor);
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    cursor.setCharFormat(charFormat);

}

