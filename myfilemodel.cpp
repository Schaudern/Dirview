#include "myfilemodel.h"

MyFileModel::MyFileModel(QObject *parent)
    : QFileSystemModel{parent}
{

}

QVariant MyFileModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole && index.column() == 1)
    {
        QFileInfo fileInfo = this->fileInfo(index);
        qint64 s = sizes(fileInfo.absoluteFilePath(), QDir::homePath());
        QString m = "B";
        float s2 = s;
        if (s > 1024)
        {
            s2 = s/1024;
            m = "KB";
        }
        if (s2 > 1024)
        {
            s2 = s2/1024;
            m = "MB";
        }
        if (s2 > 1024)
        {
            s2 = s2/1024;
            m = "GB";
        }
        return QString::number(s2, 'f', 1) + m;
    }
    return QFileSystemModel::data(index, role);
}


qint64 MyFileModel::sizes(QString path, QString Dir) const
{
    if (path.startsWith("/home/administrator/"))
        path.remove(0, QString("/home/administrator/").length());
    QDir::setCurrent(Dir);

    QFileInfo fi(path);
    qint64 t_size = 0;
    if (fi.exists() and !fi.isSymLink())
    {
        if (fi.isDir())
        {
            QDir::setCurrent(path);
            QDir dir(path);
            if (path != Dir)
                dir.setPath(Dir + "/" + path);
            QStringList entries = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden);
            int rowCount = entries.size();
            if (rowCount > 0)
            {
                QString cp = QDir::currentPath();
                for (int i = 0; i < rowCount; i++)
                {
                    t_size += sizes(entries[i], QDir::currentPath());
                    if (path != Dir)
                        QDir::setCurrent(Dir + "/" + path);
                    else
                        QDir::setCurrent(Dir);
                }
                return t_size;
            }
            else
                return 0;
        }
        else
        {
            return fi.size();
        }
    }
    else
    {
        return 0;
    }
}
