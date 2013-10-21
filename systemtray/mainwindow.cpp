/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  Gianni Rossi <gianni.rossi@bitforge.com.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QSortFilterProxyModel>

MainWindow::MainWindow(RedMineManager* _manager, QWidget* parent, Qt::WindowFlags flags): 
    QWidget(parent, flags),
    m_manager(_manager),
    m_timeEntriesModel(_manager),
    m_issuesProxyModel(new QSortFilterProxyModel(this))
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    
    connect(ui->tvIssues, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(viewDoubleClicked(QModelIndex)));
    
    connect(m_manager, SIGNAL(recievedProjectList(uint, uint, uint, ProjectVectorPtr)), &m_projectsModel, SLOT(setProjectData(uint, uint, uint, ProjectVectorPtr)));
    connect(m_manager, SIGNAL(recievedProjectList(uint, uint, uint, ProjectVectorPtr)), this, SLOT(setProjectData(uint, uint, uint, ProjectVectorPtr)));
    
    connect(m_manager, SIGNAL(recievedIssuesList(uint, uint, uint, IssueVectorPtr)), &m_issuesModel, SLOT(setIssuesData(uint, uint, uint, IssueVectorPtr)));
    connect(m_manager, SIGNAL(recievedIssuesList(uint, uint, uint, IssueVectorPtr)), this, SLOT(setIssuesData(uint, uint, uint, IssueVectorPtr)));
    
    connect(m_manager, SIGNAL(recievedTimeEntriesList(uint, uint, uint, TimeEntryVectorPtr)), this, SLOT(setTimeEntriesData(uint, uint, uint, TimeEntryVectorPtr)));
    
    m_manager->listProjects();
    m_manager->listIssues();
    m_manager->listTimeEntries();
    
    ui->tvIssues->setModel(m_issuesProxyModel);
}

void MainWindow::setProjectData(uint, uint, uint, ProjectVectorPtr)
{
}

void MainWindow::setIssuesData(uint, uint, uint, IssueVectorPtr)
{
    m_issuesProxyModel->setSourceModel(&m_issuesModel);
    ui->tvIssues->hideColumn(0);
}

void MainWindow::setTimeEntriesData(uint, uint, uint, TimeEntryVectorPtr)
{
}

void MainWindow::viewDoubleClicked(QModelIndex index)
{
    m_issuesModel.setSelected(m_issuesProxyModel->mapToSource(index));
}
