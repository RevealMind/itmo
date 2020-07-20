#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "option.h"
#include "scanner.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QTimer>
#include <QCommonStyle>
#include <QDebug>
#include <QThread>
#include <QTime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionAdd_Directory_triggered();
    void on_action_Delete_Directores_triggered();
    void on_actionDelete_selected_files_triggered();
    void on_scanButton_clicked();

    void displayMatch(std::list<QString> const& files);
    void displayError(QString const& filePath);
    void displayProgress(int progress);
    void displayResult();

    void on_subFoldersBox_stateChanged(int arg1);
private:
    std::pair<Scanner*, QThread*> createScanner();
    std::map<option, bool> getParameters();
    void displayNotification(const char* text, const char* title = "Notification", int time = 3000);
    Ui::MainWindow *ui;
    QTime timer;
};

#endif // MAINWINDOW_H
