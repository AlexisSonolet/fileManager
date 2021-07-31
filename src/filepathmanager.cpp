#include "../headers/filepathmanager.h"

filepathManager::filepathManager()
{

}

QString filepathManager::modelIndexToAbsolutePath(const QModelIndex &index, QString rootPath)
{
    QStringList rootPathParts = rootPath.split("/");
    QString rootFolder = rootPathParts.at(rootPathParts.size() - 1);

    QList<QString> folderList;

    QModelIndex currentIndex = index;
    QString current = currentIndex.data().toString();

    while (current != rootFolder && index.isValid()) {
        folderList.push_front(current);

        currentIndex = currentIndex.parent();
        current = currentIndex.data().toString();
    }
    QString finalPath = join(folderList, rootPath);

    return finalPath;
}

QString filepathManager::join(QList<QString> pathList)
{
    return join(pathList, "");
}

QString filepathManager::join(QString path, const QString prefix)
{
    QList<QString> folderList = {path};
    return join(folderList, prefix);
}

QString filepathManager::join(QList<QString> pathList, const QString prefix)
{
    pathList.push_front(prefix);
    QStringList stringList = QStringList(pathList);
    return stringList.join("/");
}
