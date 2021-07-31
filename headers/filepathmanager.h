#ifndef FILEPATHMANAGER_H
#define FILEPATHMANAGER_H

#include <QtCore>

class filepathManager
{
public:
    filepathManager();

    QString modelIndexToAbsolutePath(const QModelIndex &index, QString rootPath);

    QString join(QList<QString> pathList);
    QString join(QString path, const QString prefix);
    QString join(QList<QString> pathList, const QString prefix);
};

#endif // FILEPATHMANAGER_H
