/*
 * Copyright (C) 2018 David Herzig (dave.herzig@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "mainwidget.h"
#include "eventhandler.h"

#include <QApplication>
#include <QCoreApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow()
{
    mainWidget = new MainWidget();
    this->setCentralWidget(mainWidget);
    this->setupMenuStructure();
}

MainWindow::~MainWindow()
{
    delete mainWidget;
}

void MainWindow::setupMenuStructure()
{
    QMenuBar *menuBar = this->menuBar();

    QMenu *fileMenu = new QMenu(tr("&File"));
    QMenu *aboutMenu = new QMenu("About");

    QAction *clearAction = fileMenu->addAction("Clear");

    QObject::connect(
        clearAction, SIGNAL(triggered()),
        mainWidget, SLOT(clear()));

    fileMenu->addSeparator();

    QAction *loadAction = fileMenu->addAction("Load Model");
    QObject::connect(
        loadAction, SIGNAL(triggered()),
        mainWidget->getEventHandler(), SLOT(load()));
    QAction *saveAction = fileMenu->addAction("Save Model");
    QObject::connect(
        saveAction, SIGNAL(triggered()),
        mainWidget->getEventHandler(), SLOT(save()));


    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction("Exit");
    QObject::connect(
        exitAction, SIGNAL(triggered()),
        QCoreApplication::instance(), SLOT(quit()));

    menuBar->addMenu(fileMenu);

    QAction *aboutQTAction = aboutMenu->addAction("About QT");

    QObject::connect(
        aboutQTAction, SIGNAL(triggered()),
        QApplication::instance(), SLOT(aboutQt()));

    menuBar->addMenu(aboutMenu);
}
