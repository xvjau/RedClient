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

#ifndef RMOBJECTSUMMARY_H
#define RMOBJECTSUMMARY_H

#include <QObject>
#include <QString>
#include <QJsonObject>

class RMObjectSummary: public QObject
{
    Q_OBJECT
    
public:
    RMObjectSummary() {}
    RMObjectSummary(const RMObjectSummary &other):
        m_id(other.m_id),
        m_name(other.m_name)
    {
    }
    RMObjectSummary(RMObjectSummary &&other):
        m_id(other.m_id),
        m_name(std::move(other.m_name))
    {
    }
    
    RMObjectSummary& operator=(const RMObjectSummary& other)
    {
        m_id = other.m_id;
        m_name = other.m_name;
        return *this;
    }
    
    RMObjectSummary& operator=(RMObjectSummary&& other)
    {
        m_id = other.m_id;
        m_name = std::move(other.m_name);
        return *this;
    }
    
    RMObjectSummary(const QJsonObject &_obj):
        m_id(_obj.value("id").toString().toInt()),
        m_name(_obj.value("name").toString())
    {
    }
    
protected:
    int     m_id = 0;
    QString m_name;
    
public:
    int id() const { return m_id; }
    const QString& name() const { return m_name; }
};

#endif // RMOBJECTSUMMARY_H
