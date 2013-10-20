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

MainWindow::MainWindow(RedMineManager* _manager, QWidget* parent, Qt::WindowFlags flags): 
    QMainWindow(parent, flags),
    m_manager(_manager),
    m_timeEntriesModel(_manager)
{
    ui = new Ui::MainWindow();
    ui->setupUi(this);
    
    connect(m_manager, SIGNAL(recievedProjectList(int, int, int, ProjectVectorPtr)), &m_projectsModel, SLOT(setProjectData(int, int, int, ProjectVectorPtr)));
    connect(m_manager, SIGNAL(recievedProjectList(int, int, int, ProjectVectorPtr)), this, SLOT(setProjectData(int, int, int, ProjectVectorPtr)));
    
    connect(m_manager, SIGNAL(recievedIssuesList(int, int, int, IssueVectorPtr)), &m_issuesModel, SLOT(setIssuesData(int, int, int, IssueVectorPtr)));
    connect(m_manager, SIGNAL(recievedIssuesList(int, int, int, IssueVectorPtr)), this, SLOT(setIssuesData(int, int, int, IssueVectorPtr)));
    
    connect(m_manager, SIGNAL(recievedTimeEntriesList(int, int, int, TimeEntryVectorPtr)), this, SLOT(setTimeEntriesData(int, int, int, TimeEntryVectorPtr)));
    
    m_manager->listProjects();
    m_manager->listIssues();
    m_manager->listTimeEntries();
}

void MainWindow::setProjectData(int, int, int, ProjectVectorPtr)
{
    ui->tvProjects->setModel(&m_projectsModel);
    
    auto header = ui->tvProjects->header();
    header->swapSections(1, 4);
    
    ui->tvProjects->hideColumn(3); // identifier
    ui->tvProjects->hideColumn(5); // description
    ui->tvProjects->hideColumn(6); // parentProjectId
    
    ui->tvProjects->expandAll();
}

void MainWindow::setIssuesData(int, int, int, IssueVectorPtr)
{
    ui->tvIssues->setModel(&m_issuesModel);
}

void MainWindow::setTimeEntriesData(int, int, int, TimeEntryVectorPtr)
{
    ui->tvTimeEntries->setModel(&m_timeEntriesModel);
}


