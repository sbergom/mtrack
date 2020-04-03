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

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "tracker.h"

#define MTRACK_SUPPORTED_SCHEMA 1
#define MTRACK_NEWENTRY_ID ""

TrackedEntry::TrackedEntry(Tracker *owner, QString id)
{
  this->owner = owner;
  this->id = id;
  if (id == MTRACK_NEWENTRY_ID)
  {
    name = "";
    note = "";
    comment = "";
    date = "";
  }
  else
  {
    owner->selectEntry.addBindValue(id);
    owner->selectEntry.exec();
    QSqlRecord record = owner->selectEntry.record();
    owner->selectEntry.first();
    name = owner->selectEntry.value(record.indexOf("title")).toString();
    note = owner->selectEntry.value(record.indexOf("viewing_notes")).toString();
    comment = owner->selectEntry.value(record.indexOf("comments")).toString();
    date = owner->selectEntry.value(record.indexOf("date_viewed")).toString();
  }
}

TrackedEntry::~TrackedEntry()
{
  // TODO free resources
}

void TrackedEntry::cancelEntry()
{
  owner->reap(this);
}

void TrackedEntry::deleteEntry()
{
  if (id != MTRACK_NEWENTRY_ID)
  {
    owner->deleteEntry.addBindValue(id);
    if (!owner->deleteEntry.exec())
    {
      owner->lastError = owner->deleteEntry.lastError().text();
    }
  }
  cancelEntry();
}

void TrackedEntry::saveEntry()
{
  if (id == MTRACK_NEWENTRY_ID)
  {
    id.setNum(owner->nextId++);
    owner->insertEntry.addBindValue(id);
    owner->insertEntry.addBindValue(name);
    owner->insertEntry.addBindValue(note);
    owner->insertEntry.addBindValue(date);
    owner->insertEntry.addBindValue(comment);
    if (!owner->insertEntry.exec())
    {
      owner->lastError = owner->insertEntry.lastError().text();
    }
  }
  else
  {
    owner->updateEntry.addBindValue(name);
    owner->updateEntry.addBindValue(note);
    owner->updateEntry.addBindValue(date);
    owner->updateEntry.addBindValue(comment);
    owner->updateEntry.addBindValue(id);
    if (!owner->updateEntry.exec())
    {
      owner->lastError = owner->updateEntry.lastError().text();
    }
  }
}

Tracker::Tracker()
{
}

Tracker::Tracker(QString filename)
{
  isInError = false;
  schemaNeedsUpdating = false;
  bool exists = QFile::exists(filename);
  bool writeable = (QFile::permissions(filename)&QFileDevice::WriteUser) != 0;
  if (exists && !writeable)
  {
    isInError = true;
    lastError = "file '" + filename + "' not writeable";
    return;
  }

  db_conn = QSqlDatabase::addDatabase("QSQLITE");
  db_conn.setDatabaseName(filename);
  if (!db_conn.open())
  {
    isInError = true;
    lastError = db_conn.lastError().text();
    return;
  }

  if (!exists)
  {
    // tracker file doesn't exist, create and initialize
    db_conn.transaction();
    QSqlQuery createMetadata("create table metadata ("
                             "  key varchar(100) not null,"
                             "  value varchar(512)"
                             ")", db_conn);
    createMetadata.exec();
    QSqlQuery createTracker(" create table tracked_list ("
                            "   id integer primary key asc,"
                            "   title varchar(256) not null,"
                            "   viewing_notes varchar(512),"
                            "   date_viewed date,"
                            "   comments clob"
                            ")", db_conn);
    createTracker.exec();

    QSqlQuery insertMetadata(db_conn);
    insertMetadata.prepare("insert into metadata (key, value) values (?, ?)");
    insertMetadata.addBindValue("schema.app");
    insertMetadata.addBindValue("mtrack");
    insertMetadata.exec();
    insertMetadata.addBindValue("schema.version");
    QString version;
    version.setNum(MTRACK_SUPPORTED_SCHEMA);
    insertMetadata.addBindValue(version);
    insertMetadata.exec();

    if (!db_conn.commit())
    {
      isInError = true;
      lastError = db_conn.lastError().text();
      return;
    }
  }

  QString schemaApp = getMetaData("schema.app");
  int schemaVersion = getMetaData("schema.version").toInt();

  if (schemaApp != "mtrack")
  {
    isInError = true;
    lastError = "Not a movie tracker database";
  }
  else if (schemaVersion < MTRACK_SUPPORTED_SCHEMA)
  {
    isInError = true;
    schemaNeedsUpdating = true;
  }
  else if (schemaVersion > MTRACK_SUPPORTED_SCHEMA)
  {
    isInError = true;
    lastError = "Movie tracker file is newer than expected";
  }

  if (!isInError)
  {
    entries = new QSqlTableModel(0, db_conn);
    entries->setTable("tracked_list");

    insertEntry = QSqlQuery("insert into tracked_list "
                            "(id, title, viewing_notes, date_viewed, comments) "
                            "values (?, ?, ?, ?, ?)", db_conn);
    updateEntry = QSqlQuery("update tracked_list "
                            "set title = ?, viewing_notes = ?, "
                            "date_viewed = ?, comments = ? "
                            "where id = ?", db_conn);
    selectEntry = QSqlQuery("select * from tracked_list where id = ?", db_conn);
    deleteEntry = QSqlQuery("delete from tracked_list where id = ?", db_conn);
  }

  if (exists && !isInError)
  {
    QSqlQuery getmaxid("select max(id) from tracked_list", db_conn);
    getmaxid.exec();
    getmaxid.first();
    nextId = getmaxid.value(0).toInt() + 1;
  }
  else
  {
    nextId = 1;
  }
}

Tracker::~Tracker()
{
  this->close();
  // TODO free resources
}

void Tracker::close()
{
  // TODO
  // commit any transactions
  // shut down connection
}

QSqlTableModel* Tracker::getEntries(QString filter)
{
  if (!isInError)
  {
    entries->setFilter("title like '%" + filter.replace('\'', "''") + "%'");
    entries->setSort(1, Qt::AscendingOrder);
    entries->select();
    return entries;
  }
  return nullptr;
}

TrackedEntry* Tracker::getEntry(QString id)
{
  if (!isInError)
  {
    return new TrackedEntry(this, id);
  }
  return nullptr;
}

TrackedEntry* Tracker::newTrackedEntry()
{
  if (!isInError)
  {
    return new TrackedEntry(this, MTRACK_NEWENTRY_ID);
  }
  return nullptr;
}

bool Tracker::needsUpdating()
{
  return schemaNeedsUpdating;
}

bool Tracker::updateSchema()
{
  // TODO
  // TODO after (successfully) updating need to finish initialization
  // when updated, schemaNeedsUpdating = false
  return !schemaNeedsUpdating;
}

QString Tracker::getMetaData(QString property)
{
  if (!isInError)
  {
    QSqlQuery mdQuery(db_conn);
    mdQuery.prepare("select value from metadata where key = ?");
    mdQuery.addBindValue(property);
    mdQuery.exec();
    QSqlRecord record = mdQuery.record();
    if (mdQuery.first())
    {
      return mdQuery.value(record.indexOf("value")).toString();
    }
  }
  return "";
}

void Tracker::reap(TrackedEntry *entry)
{
  // TODO more?
  delete entry;
}
