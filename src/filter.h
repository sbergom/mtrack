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
#ifndef FILTER_H
#define FILTER_H

#include <QLineEdit>
#include <QListWidget>
#include <QWidget>

#include "tracker.h"
#include "entry.h"

/*!
  \class TrackerFilter
  \brief Manage the widgets used to search a tracked list

  The TrackerFilter coordinates the widgets used to search and select
  entries in a tracked list.  It is also responsible for maintaining
  the opened Tracker and saving it when needed.
 */
class TrackerFilter : public QWidget
{
  Q_OBJECT;
public:
  explicit TrackerFilter(EntryField *entry, QWidget *parent = nullptr);

  /*!
    \fn void TrackerFilter::setTracker(Tracker *newTracker)

    Set the current tracker file.  If the filter already has an open
    tracker, close it, discarding any unsaved edits made to an entry.
   */
  void setTracker(Tracker *newTracker);

  /*!
    \fn void TrackerFilter::closeTracker()

    Close the tracker file.
   */
  void closeTracker();

  /*!
    \fn const QString TrackerFilter::getFilterText()

    Get the text that is currently in the search field.
   */
  const QString getFilterText();

private:
  QPushButton *newButton;
  QLineEdit *filterBox;
  QListView *filterResults;
  Tracker   *tracker;

  EntryField *fieldEditor;

signals:

public slots:

  /*!
    \fn void TrackerFilter::newTrackedEntry()

    Create a new tracked entry to be edited in the associated
    EntryField.
   */
  void newTrackedEntry();

  /*!
    \fn void refilterResults(const QString &text)

    Update the results according to changes in the search box.
   */
  void refilterResults(const QString &text);

  /*!
    \fn void selectResult(const QModelIndex&)

    Update the EntryField in response to a selected item in the filter
    results.
   */
  void selectResult(const QModelIndex&);
};

#endif // FILTER_H
