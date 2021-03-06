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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "redminemanager.h"
#include "projectsmodel.h"
#include "issuesmodel.h"
#include "timeentriesmodel.h"
#include "usersmodel.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(RedMineManager *_manager, QWidget* parent = 0, Qt::WindowFlags flags = 0);
    
private:
    Ui::MainWindow* ui = nullptr;
    
    RedMineManager  *m_manager = nullptr;
    
    ProjectsModel       m_projectsModel;
    IssuesModel         m_issuesModel;
    TimeEntriesModel    m_timeEntriesModel;
    UsersModel          m_usersModel;

private slots:
    void setProjectData(uint, uint, uint, ProjectVectorPtr);
    void setIssuesData(uint, uint, uint, IssueVectorPtr);
    void setTimeEntriesData(uint, uint, uint, TimeEntryVectorPtr);
    void setUsersData(uint,uint,uint,UserVectorPtr);
};

#endif // MAINWINDOW_H
