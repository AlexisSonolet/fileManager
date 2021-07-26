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
    // -> Top view
    //   -> Search view
    ui->search_fileName_cb->setCheckState(Qt::CheckState::Checked);
    ui->search_folderName_cb->setCheckState(Qt::CheckState::Checked);
    ui->search_fileContent_cb->setCheckState(Qt::CheckState::Unchecked);
    // -> Left view
    //   -> Favorites
    QListWidget* list = ui->favoritesListView;
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setFixedHeight(list->sizeHintForRow(0) * list->count() + 2 * list->frameWidth());

    //   -> treeWidget
    setupFileSystemModel();

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

void MainWindow::setupFileSystemModel()
{
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(QDir::currentPath());
    qDebug() << QDir::currentPath();
    dirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QStringList stringFilter;
    stringFilter << "[A-z]*"; // Don't keep files that begin by "."
    dirModel->setNameFilters(stringFilter);
    dirModel->setNameFilterDisables(false);

    // Setup the view
    ui->folderTreeView->setModel(dirModel);
    ui->listView->setModel(dirModel);

    // Setup the root dir
    const QString rootPath = QDir::homePath();
    ui->folderTreeView->setRootIndex(dirModel->index(rootPath));

    // Hide other columns
    for (int i=1; i < dirModel->columnCount(); i++) {
        ui->folderTreeView->hideColumn(i);
    }

    // Set the width
    int splitterSize = ui->splitter->sizeHint().rwidth();
    qDebug() << splitterSize;
    QList<int> sizeList = {100, splitterSize - 100};
    ui->splitter->setSizes(sizeList);

    ui->listView->setViewMode(QListView::ViewMode::ListMode);
}


void MainWindow::on_folderTreeView_activated(const QModelIndex &index)
{
    ui->listView->setRootIndex(index);
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    ui->listView->setRootIndex(index);
    ui->folderTreeView->setCurrentIndex(index);
    ui->folderTreeView->expand(index);
}
