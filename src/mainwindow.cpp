/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * https://lxqt.org
 *
 * Copyright: 2012 Razor team
 * Authors:
 *   Petr Vanek <petr@scribus.info>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include <stdio.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(const QString &prompt, QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setupUi(this);
    promptLabel->setText(prompt);
    passwordEdit->setFocus(); // needed with Qt >= 6.6.1
}

MainWindow::~MainWindow()
{
}

void MainWindow::accept()
{
    puts(passwordEdit->text().toUtf8().constData());
    qApp->exit(0);
}

void MainWindow::reject()
{
    qApp->exit(1);
}
