/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QScreen>
#include <QScroller>
#include <QTreeView>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDebug>
#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QObject>
#include <QSortFilterProxyModel>
#include <window.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window win(QDir::homePath());
    win.showWindow("Dir View");

    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Dir View Example");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dontUseCustomDirectoryIconsOption("c", "Set QFileSystemModel::DontUseCustomDirectoryIcons");
    parser.addOption(dontUseCustomDirectoryIconsOption);
    QCommandLineOption dontWatchOption("w", "Set QFileSystemModel::DontWatch");
    parser.addOption(dontWatchOption);
    parser.addPositionalArgument("directory", "The directory to start in.");
    parser.process(app);

    if (parser.isSet(dontUseCustomDirectoryIconsOption))
        win.model.setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if (parser.isSet(dontWatchOption))
        win.model.setOption(QFileSystemModel::DontWatchForChanges);

    // Demonstrating look and feel features
    win.tree->setAnimated(false);
    win.tree->setIndentation(20);
    win.tree->setSortingEnabled(true);
    const QSize availableSize = win.tree->screen()->availableGeometry().size();
    win.tree->resize(availableSize / 2);
    win.tree->setColumnWidth(0, win.tree->width() / 3);

    // Make it flickable on touchscreens
    QScroller::grabGesture(win.tree, QScroller::TouchGesture);

    win.tree->setWindowTitle(QObject::tr("Dir View"));
    win.tree->show();

    return app.exec();
}
