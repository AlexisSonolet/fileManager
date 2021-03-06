#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filepathmanager.h"
#include "foldertab.h"

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QDir>
#include <QFileSystemModel>
#include <QListView>
#include <QTreeView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Setup widgets
    void setupFileSystemModel();

private slots:
    void on_searchSettigns_pb_clicked();

    void on_displaySettings_pb_clicked();

    void on_folderTreeView_activated(const QModelIndex &index);

    void on_listView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    bool isOsLinux = false;
    bool isOsWin = false;

    // Setup widgets
    QFileSystemModel *treeDirModel;
    QFileSystemModel *listDirModel;

    // Current directory
    QDir currentDir;
    QString rootPath;

    QList<folderTabWidget> tabList;
    int currentTabIndex = 0;

    // Filepath manager
    filepathManager FilePaths;
};
#endif // MAINWINDOW_H
