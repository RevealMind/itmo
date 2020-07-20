#ifndef INDEXERPROGRESSDIALOG_H
#define INDEXERPROGRESSDIALOG_H

#include <QDialog>
#include <QThread>

namespace Ui {
class indexerProgressDialog;
}

class IndexerProgressDialog : public QDialog
{
    Q_OBJECT

public:
    IndexerProgressDialog(QThread*, QWidget *parent = nullptr);
    ~IndexerProgressDialog();

private:
    Ui::indexerProgressDialog *ui;
    QThread *indexingThread;
    int totalFiles;
    int indexedFiles;
    void exit();
public slots:
    void setRange(int);
    void update();
};

#endif // INDEXERPROGRESSDIALOG_H
