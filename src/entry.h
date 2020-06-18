/* 
 * This file is part of the Movie Tracker distribution.
 * Copyright (c) 2020 Steven Bergom.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 2.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ENTRY_H
#define ENTRY_H

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "tracker.h"

class TrackerFilter;

/*!
  \class EntryField
  \brief Provides fields to edit a Tracker entry

  This class manages the widgets used to create and edit entries in a
  tracked list.
 */
class EntryField : public QWidget
{
  Q_OBJECT;
public:
  explicit EntryField(QWidget *parent = nullptr);

  /*!
    \fn void EntryField::setFilter(TrackerFilter *f)

    Sets the TrackerFilter object for communications needs.
  */
  void setFilter(TrackerFilter *f) { filter = f; }

  /*!
    \fn void EntryField::setTrackedEntry(TrackedEntry *entry)

    Sets the entry that is to be edited.  If there already exists an
    entry its newly-entered data is cleared and it is given back to
    its owner to be reclaimed.
  */
  void setTrackedEntry(TrackedEntry *entry);

  /*!
    \fn void EntryField::closeTrackedEntry()

    Close the tracked entry and give it back to its owner to be reclaimed.
  */
  void closeTrackedEntry();

private:
  QLineEdit *title;
  QLineEdit *notes;
  QLineEdit *date;
  QTextEdit *comments;
  QPushButton *saveButton;
  QPushButton *cancelButton;
  QPushButton *deleteButton;
  TrackedEntry *entry;
  TrackerFilter *filter;
  bool hasModifications;
  
signals:

public slots:

  /*!
    \fn void EntryField::deleteTrackedEntry()

    Delete the entry from the tracked list.
  */
  void deleteTrackedEntry();

  /*!
    \fn void EntryField::saveTrackedEntry()

    Save the newly entered data for the tracked entry.
  */
  void saveTrackedEntry();

  /*!
    \fn void EntryField::cancelTrackedEntry()

    Throw away any changes made to the tracked entry.
  */
  void cancelTrackedEntry();

  /*!
    \fn void EntryField::entryModified()

    Signal that an entry has been modified and change the UI as
    necessary.
  */
  void entryModified();

  /*!
    \fn void EntryField::entryModified()

    Signal that an entry has been modified and change the UI as
    necessary.
  */
  void entryModified(const QString &value);
};

#endif // ENTRY_H
