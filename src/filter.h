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
#ifndef FILTER_H
#define FILTER_H

#include <QLineEdit>
#include <QListWidget>
#include <QWidget>

#include "tracker.h"
#include "entry.h"

class TrackerFilter : public QWidget
{
  Q_OBJECT;
public:
  explicit TrackerFilter(EntryField *entry, QWidget *parent = nullptr);

  void setTracker(Tracker *newTracker);
  void closeTracker();

private:
  QLineEdit *filterBox;
  QListView *filterResults;
  Tracker   *tracker;

  EntryField *fieldEditor;

signals:

public slots:
  void refilterResults(const QString &text);
  void selectResult(const QModelIndex&);
};

#endif // FILTER_H
