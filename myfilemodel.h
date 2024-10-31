#ifndef MYFILEMODEL_H
#define MYFILEMODEL_H

#include <QFileSystemModel>
#include <QVariant>
#include <QDebug>
#include <QApplication>


class Window;

class MyFileModel : public QFileSystemModel
{
public:
    explicit MyFileModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    qint64 sizes(QString path, QString Dir) const;
};

#endif // MYFILEMODEL_H
