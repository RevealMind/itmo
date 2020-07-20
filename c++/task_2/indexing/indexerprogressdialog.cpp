#include "indexerprogressdialog.h"
#include "ui_indexerprogressdialog.h"


IndexerProgressDialog::IndexerProgressDialog(QThread* indexingThread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::indexerProgressDialog),
    indexingThread(indexingThread),
    totalFiles(0),
    indexedFiles(0)
{
    ui->setupUi(this);
    connect(ui->cancleButton, &QPushButton::clicked, indexingThread, &QThread::requestInterruption);
    connect(this, &QDialog::rejected, indexingThread, &QThread::requestInterruption);
}

IndexerProgressDialog::~IndexerProgressDialog()
{
    delete ui;
}

void IndexerProgressDialog::setRange(int max){
    ui->progressBar->setRange(0,max);
    this->setWindowTitle("Indexing...");
    totalFiles = max;
}

void IndexerProgressDialog::update(){
    ui->label->setText(QString("%1 / %2 have already indexed").arg(++indexedFiles).arg(totalFiles));
    ui->progressBar->setValue(indexedFiles);
}

void IndexerProgressDialog::exit() {
    close();
}
