// albert - a simple application launcher for linux
// Copyright (C) 2014-2017 Manuel Schneider
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QDebug>
#include "item.h"
#include "matchcompare.h"
#include "query.h"


/** ***************************************************************************/
const QString &Core::Query::string() const {
    return string_;
}


/** ***************************************************************************/
const QString &Core::Query::rawString() const {
    return rawString_;
}


/** ***************************************************************************/
bool Core::Query::isTriggered() const {
    return !trigger_.isNull();
}


/** ***************************************************************************/
const QString &Core::Query::trigger() const {
    return trigger_;
}


/** ***************************************************************************/
bool Core::Query::isValid() const {
    return isValid_;
}


/** ***************************************************************************/
void Core::Query::addMatchWithoutLock(const std::shared_ptr<Core::Item> &item, uint score) {
    auto it = scores_.find(item->id());
    if ( it == scores_.end() )
        results_.emplace_back(item, score/2);
    else
        results_.emplace_back(item, (static_cast<ulong>(score)+it->second)/2);
}


/** ***************************************************************************/
void Core::Query::addMatchWithoutLock(std::shared_ptr<Core::Item> &&item, uint score) {
    auto it = scores_.find(item->id());
    if ( it == scores_.end() )
        results_.emplace_back(std::move(item), score/2);
    else
        results_.emplace_back(std::move(item), (static_cast<ulong>(score)+it->second)/2);
}
