/* 
 * This file is part of the Movie Tracker distribution.
 * Copyright (c) 2020 Steven Bergom.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "tracker.h"

TrackedEntry::TrackedEntry(QString id)
{
  if (id == "")
  {
    // TODO initialize defaults
  }
  else
  {
    // TODO read from stream
  }
}

TrackedEntry::~TrackedEntry()
{
  cancelEntry();
  // TODO free resources
}

void TrackedEntry::cancelEntry()
{
  // TODO
}

void TrackedEntry::saveEntry()
{
  // TODO
}

Tracker::Tracker()
{
}

Tracker::Tracker(QString filename)
{
  // TODO 
}

Tracker::~Tracker()
{
  this->close();
  // TODO free resources
}

void Tracker::close()
{
  // TODO 
}

void Tracker::getEntries(QString filter)
{
  // TODO
}

TrackedEntry* Tracker::getEntry(QString id)
{
  // TODO
  return nullptr;
}

TrackedEntry* Tracker::newTrackedEntry()
{
  // TODO
  return nullptr;
}

bool Tracker::needsUpdating()
{
  // TODO
  return false;
}

bool Tracker::updateSchema()
{
  // TODO
  return false;
}

QString Tracker::getMetaData(QString property)
{
  // TODO 
}
