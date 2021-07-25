#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>

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
    void setupFileSystemTreeWidget();

private slots:
    void on_searchSettigns_pb_clicked();

private:
    Ui::MainWindow *ui;
    bool isOsLinux = false;
    bool isOsWin = false;

    // Setup widgets
    QFileSystemModel *dirModel;
};
#endif // MAINWINDOW_H
