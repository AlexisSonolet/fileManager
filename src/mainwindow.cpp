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
    treeDirModel = new QFileSystemModel(this);
    listDirModel = new QFileSystemModel(this);
    treeDirModel->setRootPath(QDir::currentPath());
    listDirModel->setRootPath(QDir::currentPath());
    qDebug() << QDir::currentPath();
    treeDirModel->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    listDirModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QStringList stringFilter;
    stringFilter << "[A-z]*"; // Don't keep files that begin by "."
    treeDirModel->setNameFilters(stringFilter);
    listDirModel->setNameFilters(stringFilter);
    treeDirModel->setNameFilterDisables(false);
    listDirModel->setNameFilterDisables(false);

    // Setup the view
    ui->folderTreeView->setModel(treeDirModel);
    ui->listView->setModel(listDirModel);

    // Setup the root dir
    rootPath = QDir::homePath();

    ui->folderTreeView->setRootIndex(treeDirModel->index(rootPath));
    ui->listView->setRootIndex(listDirModel->index(rootPath));

    // Hide other columns of treeDirModel
    for (int i=1; i < treeDirModel->columnCount(); i++) {
        ui->folderTreeView->hideColumn(i);
    }

    // Set the width
    int splitterSize = ui->splitter->sizeHint().rwidth();
    QList<int> sizeList = {100, splitterSize - 100};
    ui->splitter->setSizes(sizeList);

    ui->listView->setViewMode(QListView::ViewMode::ListMode);
}


void MainWindow::on_folderTreeView_activated(const QModelIndex &index)
{
    QString path = FilePaths.modelIndexToAbsolutePath(index, rootPath);

    ui->listView->setRootIndex(listDirModel->index(path));
}

void MainWindow::on_listView_activated(const QModelIndex &index)
{
    ui->listView->setRootIndex(index);
    ui->folderTreeView->setCurrentIndex(index);
    ui->folderTreeView->expand(index);
}
