#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup OS
#ifdef Q_OS_LINUX
    isOsLinux = true;
#endif
#ifdef Q_OS_WIN
    isOsWin = true;
#endif

    if (isOsLinux) {
        qDebug("OS : Linux");
    }
    if (isOsWin) {
        qDebug("OS : Windows");
    }


    // Hide search tab layout
    ui->searchTabLayout->hide();

    // Setup widgets
    setupFileSystemTreeWidget();
    ui->search_fileName_cb->setCheckState(Qt::CheckState::Checked);
    ui->search_folderName_cb->setCheckState(Qt::CheckState::Checked);
    ui->search_fileContent_cb->setCheckState(Qt::CheckState::Unchecked);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_searchSettigns_pb_clicked()
{
    if (ui->searchTabLayout->isVisible()) {
        ui->searchTabLayout->hide();
    } else {
        ui->searchTabLayout->show();
    }
}

void MainWindow::setupFileSystemTreeWidget()
{
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::currentPath());
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);

    // Setup the view
    ui->folderTreeView->setModel(dirModel);

    // Hide other columns
    for (int i=1; i < dirModel->columnCount(); i++) {
        ui->folderTreeView->hideColumn(i);
    }

    // Set the width
    int splitterSize = ui->splitter->sizeHint().rwidth();
    qDebug() << splitterSize;
    QList<int> sizeList = {100, splitterSize - 100};
    ui->splitter->setSizes(sizeList);
}
