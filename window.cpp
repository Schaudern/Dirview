#include "window.h"

Window::Window(QObject *parent)
    : QObject{parent}
{

}

Window::Window(QString RootPath)
{
    QDir::setCurrent(QDir::homePath());
    rootPath = RootPath;
    model.setRootPath(rootPath);
    model.setFilter(QDir::Filters(QDir::AllEntries | QDir::Hidden) | QDir::NoDotAndDotDot);
    tree = new QTreeView();
    edit = new QLineEdit(tree);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(edit);
    layout->addWidget(tree);
    const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
    qApp->processEvents();
    window.setLayout(layout);
    QObject::connect(edit, &QLineEdit::textChanged, this, &Window::filter);
    proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(&model);
    proxyModel->setRecursiveFilteringEnabled(true);
    tree->setModel(proxyModel);
    qApp->processEvents();
    tree->setRootIndex(proxyModel->mapFromSource(rootIndex));
}


void Window::showWindow(const char *winTitle)
{
    tree->setWindowTitle(QObject::tr(winTitle));
    tree->show();
    window.show();
}

void Window::filter(const QString& str)
{
    qDebug() << str;
    model.setRootPath(rootPath);
    model.setFilter(QDir::Filters(QDir::AllEntries | QDir::Hidden) | QDir::NoDotAndDotDot);
    proxyModel->setSourceModel(&model);
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterRegularExpression(QRegularExpression(str, QRegularExpression::CaseInsensitiveOption));
    qDebug() << proxyModel->filterRegularExpression();
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setRecursiveFilteringEnabled(true);
    proxyModel->invalidate();
    tree->setModel(proxyModel);
    const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
    tree->setRootIndex(proxyModel->mapFromSource(rootIndex));
}













