#include "mainwindow.h"

#include "QColor"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QCommonStyle style;
    ui->actionAdd_Directory->setIcon(style.standardIcon(QCommonStyle::SP_DialogOpenButton));
    ui->action_Delete_Directores->setIcon(style.standardIcon(QCommonStyle::SP_TrashIcon));
    ui->actionExit->setIcon(style.standardIcon(QCommonStyle::SP_DialogCancelButton));
    ui->actionDelete_selected_files->setIcon(style.standardIcon(QCommonStyle::SP_DialogResetButton));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionAdd_Directory_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory for Scanning",
                                                      QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (dir != nullptr) {

        int topCount = ui->dirsTreeWidget->topLevelItemCount();
        for (int i = 0; i < topCount; ++i) {
            QTreeWidgetItem* curItem = ui->dirsTreeWidget->topLevelItem(i);
            QString curDir = curItem->text(0);
            if (dir == curDir || dir.contains(curDir + ((curDir.back() == "/")? "" : "/"))) {
                displayNotification("Directory has already been added");
                return;
            }
            if (curDir.contains(dir + ((dir.back() == "/")? "" : "/"))) {
                delete curItem;
                topCount--;
                i--;
            }
        }
        QTreeWidgetItem* item = new QTreeWidgetItem;
        item->setText(0, dir);
        ui->dirsTreeWidget->addTopLevelItem(item);
        ui->dirsTreeWidget->header()->resizeSections(QHeaderView::ResizeToContents);
    }
}

void MainWindow::on_action_Delete_Directores_triggered()
{
    if (ui->dirsTreeWidget->selectedItems().empty()) {
        displayNotification("Please, select elements you want to delete");
    }
    for (auto item : ui->dirsTreeWidget->selectedItems()) {
        delete item;
    }
}

void MainWindow::displayNotification(const char* text, const char* title, int time) {
    QMessageBox* masBox = new QMessageBox(QMessageBox::Information,
                                          QString(title),
                                          QString(text),
                                          QMessageBox::StandardButtons(QMessageBox::Ok),
                                          this);
    masBox->show();
    QTimer::singleShot(time, masBox, SLOT(close()));

}

void MainWindow::on_scanButton_clicked()
{
    timer.start();
    ui->filesTreeWidget->clear();
    ui->scanButton->setDisabled(true);
    ui->action_Delete_Directores->setDisabled(true);
    ui->actionAdd_Directory->setDisabled(true);
    ui->toolBar->setDisabled(true);
    ui->subFoldersBox->setVisible(false);
    ui->progressBar->setVisible(true);
    ui->statusBar->showMessage("Search duplicates...");
    std::list<QString> dirs;
    int topCount = ui->dirsTreeWidget->topLevelItemCount();
    for (int i = 0; i < topCount; i++) {
        dirs.push_back(ui->dirsTreeWidget->topLevelItem(i)->text(0));
    }
    QThread* workThread = new QThread();
    Scanner* scanner = new Scanner(dirs, getParameters());
    scanner->moveToThread(workThread);

    connect(scanner, &Scanner::foundMatch, this, &MainWindow::displayMatch);
    connect(scanner, &Scanner::foundError, this, &MainWindow::displayError);
    connect(scanner, &Scanner::progress, this, &MainWindow::displayProgress);

    connect(ui->cancelButton, &QPushButton::clicked, workThread, &QThread::requestInterruption);

    connect(workThread, &QThread::started, scanner, &Scanner::scan);

    connect(scanner, &Scanner::finished, this, &MainWindow::displayResult);
    connect(scanner, &Scanner::finished, scanner, &Scanner::deleteLater);
    connect(scanner, &Scanner::finished, workThread, &QThread::quit);

    connect(workThread, &QThread::finished, workThread, &QThread::deleteLater);

    workThread->start();
}

std::map<option, bool> MainWindow::getParameters() {
    std::map<option, bool> result;
    result[option::SubFolders] = ui->subFoldersBox->checkState();
    return result;
}

void MainWindow::displayMatch(std::list<QString> const& files) {
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->filesTreeWidget);
    item->setText(0, QString("Found ") + QString::number(files.size()) + QString(" duplicates"));
    item->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsEnabled);
    for (QFileInfo dup : files) {
       QTreeWidgetItem* childItem = new QTreeWidgetItem();
       childItem->setText(0, dup.filePath());
       item->addChild(childItem);
    }
    ui->filesTreeWidget->addTopLevelItem(item);
}

void MainWindow::displayError(QString const& filePath) {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, filePath);
    item->setFlags(Qt::ItemIsEnabled);
    ui->errorsTreeWidget->addTopLevelItem(item);
}

void MainWindow::displayProgress(int progress) {
    ui->progressBar->setValue(progress);
}

void MainWindow::displayResult() {
    ui->statusBar->showMessage(QString("Finished in ") + QString::number(timer.elapsed() / 1000.0) + QString(" sec"));
    ui->scanButton->setDisabled(false);
    ui->action_Delete_Directores->setDisabled(false);
    ui->actionAdd_Directory->setDisabled(false);
    ui->toolBar->setDisabled(false);
    ui->subFoldersBox->setVisible(true);
    ui->progressBar->setVisible(false);
    if (ui->filesTreeWidget->invisibleRootItem()->childCount() == 0) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, "Duplicates not found");
        item->setFlags(Qt::ItemIsEnabled);
        ui->filesTreeWidget->addTopLevelItem(item);
    }
}

void MainWindow::on_actionDelete_selected_files_triggered()
{
    auto list = ui->filesTreeWidget->selectedItems();
    if (list.size() == 0) {
        displayNotification("Please, choose files to delete");
        return;
    }
    QMessageBox dialog;
    dialog.setWindowTitle("Confirm");
    dialog.setText("Are you sure you want to delete this file(s)?");
    dialog.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    dialog.setDefaultButton(QMessageBox::Cancel);
    if (dialog.exec() == QMessageBox::Ok) {
        int amount = 0;
        for (auto it : list) {
            QFile curFile(it->text(0));
            if (!curFile.permissions().testFlag(QFileDevice::WriteUser) || !curFile.remove()) {
                it->setTextColor(0, QColor(200, 0, 0));
            } else {
                amount++;
                QTreeWidgetItem* parent_item = it->parent();
                parent_item->removeChild(it);
                if (parent_item->childCount() == 0) {
                    ui->filesTreeWidget->invisibleRootItem()->removeChild(parent_item);
                }
            }
        }
        QString message = QString("Deleted ") + QString::number(amount) + QString(" files. ");
        if (amount < list.size()) {
            message += QString("Can't delete " + QString::number(list.size() - amount) + QString(" files"));
        }
        ui->statusBar->showMessage(message);
    }
}

void MainWindow::on_subFoldersBox_stateChanged(int arg1)
{
    ui->dirsTreeWidget->clear();
    ui->errorsTreeWidget->clear();
    ui->filesTreeWidget->clear();
}
