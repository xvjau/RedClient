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

#include "rmreqtimeentry.h"
#include "redminemanager.h"

#include <QDebug>
#include <QJsonArray>

RMReqTimeEntry::RMReqTimeEntry(RedMineManager* manager): 
    RMRequest(manager)
{
}

QUrl RMReqTimeEntry::buildUrl()
{
    QUrl result(m_manager->baseUrl());
    result.setPath("/time_entries.json");
    return result;
}

void RMReqTimeEntry::replyFinished(QNetworkReply* reply)
{
    processReply<RMTimeEntry>(reply, "time_entries", 
                              [this] (int limit, int offset, const TimeEntryVectorPtr &data)
                              { emit recievedTimeEntryList(limit, offset, data); });
}

#include "rmreqtimeentry.moc"
