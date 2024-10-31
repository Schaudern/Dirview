#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QWidget>
#include <QTreeView>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDebug>
#include <QRegularExpression>
#include <QRegExp>
#include <QFileInfo>
#include <QApplication>
#include "myfilemodel.h"

class MyFileModel;

class Window : public QObject
{
    Q_OBJECT
public:
    explicit Window(QObject *parent = nullptr);
    MyFileModel model;
    QSortFilterProxyModel *proxyModel;
    QWidget window;
    QTreeView *tree;
    QLineEdit *edit;
    QString rootPath;

    explicit Window(QString rootPath);
    void showWindow(const char *winTitle);

public slots:
    void filter(const QString& str);

signals:

};

#endif // WINDOW_H
