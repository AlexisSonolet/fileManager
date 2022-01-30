#ifndef FOLDERTAB_H
#define FOLDERTAB_H

#include <QDir>
#include <QWidget>
#include <QLabel>


enum class folderDisplayMode
{
    BIG,
    MIDDLE_SIZE,
    LIST
};


class folderTabWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Priority)

public:
    folderTabWidget(QWidget *parent = nullptr);
    folderTabWidget(folderTabWidget &oldTab, QWidget *parent = nullptr);

    void setPath(QString path);

    QString getPath();

private:
    QString *tabName;

    QDir currentDir = QDir::homePath();
    QString rootPath;

    folderDisplayMode mode = folderDisplayMode::MIDDLE_SIZE;
};


#endif // FOLDERTAB_H
