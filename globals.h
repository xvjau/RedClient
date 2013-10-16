/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  Gianni Rossi <gianni.rossi@gmail.com>
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

#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <QStringList>
#include <QDateTime>

inline QDateTime jsonDate(QString str)
{
    auto tokens = str.split(" ");
    
    QDateTime result;
    
    switch(tokens.size())
    {
        case 3:
        {
            int offset = tokens[2].toInt();
            offset = ((offset / 100) * 60 * 60) +
                    ((offset % 100) * 60);
            
            result.setUtcOffset(offset);
        }   
        case 2: result.setTime(QTime::fromString(tokens[1], "hh:mm:ss"));
        case 1: result.setDate(QDate::fromString(tokens[0], "yyyy/MM/dd"));
    }

    return result;
}

#endif // __GLOBALS_H