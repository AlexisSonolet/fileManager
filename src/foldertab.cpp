#include "../headers/foldertab.h"


folderTabWidget::folderTabWidget(QWidget *parent)
{

}

folderTabWidget::folderTabWidget(folderTabWidget &oldTab, QWidget *parent)
{
    currentDir = oldTab.currentDir;
}


void folderTabWidget::setPath(QString path)
{
    rootPath = path;
}
