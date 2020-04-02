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
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

class Tracker;
class TrackedEntry;

/*
 * create table metadata (
 *   key varchar(100) not null,
 *   value varchar(512)
 * );
 *
 * create table tracked_list (
 *   id integer primary key asc,
 *   title varchar(256) not null,
 *   viewing_notes varchar(512),
 *   date_viewed date,
 *   comments clob
 * );
 */

/*!
  \class TrackedEntry
  \brief An item in the tracked list

  The TrackedEntry is an entry in the list of the tracker file.  The
  entry contains the following data:
  \list
    \li \c name The title of the item
    \li \c note A note about where the item can be viewed
    \li \c comment Comments after viewing the item
    \li \c date The date on which the item was viewed
  \endlist
 */
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

  QString getDate() { return date; }
  void setDate(QString d) { date = d; }

  /*!
    \fn void TrackedEntry::cancelEntry()

    Delete the entry.  Any pending operations are rolled back.  If the
    entry has not committed, it is deleted as if it never existed.
   */
  void cancelEntry();

  /*!
    \fn void TrackedEntry::saveEntry()

    Commit changes to the entry.  If the entry hasn't been created
    yet, it will be at this time.
   */
  void saveEntry();

  friend class Tracker;

private:
  TrackedEntry(Tracker *owner, QString id);

  QString id;
  QString name;
  QString note;
  QString comment;
  QString date;
  Tracker *owner;
};

/*!
  \class Tracker
  \brief Encapsulate and manage a tracked file

  A Tracker file is a SQLite file with a simple schema used to keep
  track of lists of things to be viewed eg. movies.
 */
class Tracker
{
public:
  explicit Tracker();

  /*!
    \fn Tracker::Tracker(QString filename)

    Open the tracker specified by the filename.  If the file does not
    exist, create it unless the user does not have permission.  If
    there are any problems opening or initializing the file, set the
    error state and refuse any operations.
   */
  Tracker(QString filename);

  ~Tracker();


  /*!
    \fn void Tracker::close()

    Close the tracker file.  If there are any pending edits throw them
    away.
   */
  void close();

  /*!
    \fn QSqlTableModel* Tracker::getEntries(QString filter)

    Gets a list of entries filtered on the title field.  The filter is
    a case-insensitive substring match.
   */
  QSqlTableModel* getEntries(QString filter);

  /*!
    \fn TrackedEntry* Tracker::getEntry(QString id)

    Get the TrackedEntry item specified by \c id.
   */
  TrackedEntry* getEntry(QString id);

  /*!
    \fn TrackedEntry* Tracker::newTrackedEntry()

    Create a new TrackedEntry item associated with this file.  The
    data will not be persisted until the \c saveEntry() call is made.
   */
  TrackedEntry* newTrackedEntry();

  /*!
    \fn bool Tracker::needsUpdating()

    Return \c true if the schema needs to be updated to match what the
    currently executing program expects.  Until it is updated the file
    will be considered to be in error.
   */
  bool needsUpdating();

  /*!
    \fn bool Tracker::updateSchema()

    Update the schema of the file to the currently expected schema.
    Afterwards the file will no longer be considered to be in error.
   */
  bool updateSchema();

  /*!
    \fn QString Tracker::getMetaData(QString property)

    Get metadata associated with the file and specified by \c
    property.
   */
  QString getMetaData(QString property);


  /*!
    \fn bool Tracker::hasError()

    Return \c true if the file has had some kind of error.  The file
    is considered to be in error if operations on the file are
    inadvisable (eg. the schema is wrong, the file is open read-only).
   */
  bool hasError() { return isInError; }

  /*!
    \fn QString Tracker::getLastError()

    Retrieve a descriptive text of the last error.
   */
  QString getLastError() { return lastError; }

  friend class TrackedEntry;

private:
  void reap(TrackedEntry *entry);
  
  QSqlDatabase db_conn;
  QSqlTableModel *entries;
  QString lastError;
  bool isInError;
  bool schemaNeedsUpdating;

  QSqlQuery insertEntry;
  QSqlQuery updateEntry;
  QSqlQuery selectEntry;

  int nextId;
};

#endif // TRACKER_H
