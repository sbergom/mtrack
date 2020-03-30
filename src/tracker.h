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
#ifndef TRACKER_H
#define TRACKER_H

#include <QDate>
#include <QList>
#include <QString>

class TrackedEntry
{
public:
  ~TrackedEntry();

  QString getID() { return id; }

  QString getName() { return name; }
  void setName(QString n) { name = n; }

  QString getNote() { return note; }
  void setNote(QString n) { note = n; }

  QString getComment() { return comment; }
  void setComment(QString n) { comment = n; }

  QDate getDate() { return date; }
  void setDate(QDate d) { date = d; }

  // Delete the entry.  Any pending operations are rolled back.  If
  // the entry has not committed, it is deleted as if it never existed.
  void cancelEntry();

  // Commit changes to the entry.  If the entry hasn't been created
  // yet, it will be at this time.
  void saveEntry();

  friend class Tracker;

private:
  TrackedEntry(QString id);

  QString id;
  QString name;
  QString note;
  QString comment;
  QDate date;
};

class Tracker
{
public:
  explicit Tracker();
  Tracker(QString filename);
  ~Tracker();

  void close();
  // TODO this should be an iterator
  void getEntries(QString filter);
  TrackedEntry* getEntry(QString id);
  TrackedEntry* newTrackedEntry();

  bool needsUpdating();
  bool updateSchema();
  QString getMetaData(QString property);

  QString getLastError() { return lastError; }

private:
  QString lastError;
};

#endif // TRACKER_H
