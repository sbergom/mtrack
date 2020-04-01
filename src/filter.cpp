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
#include <QVBoxLayout>
#include <QAbstractItemModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QDebug>
#include "filter.h"

TrackerFilter::TrackerFilter(EntryField *entry, QWidget *parent) : QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout;

  filterBox = new QLineEdit;
  filterResults = new QListView;
  filterResults->setSelectionMode(QAbstractItemView::SingleSelection);

  connect(filterResults, SIGNAL(clicked(const QModelIndex&)),
          this, SLOT(selectResult(const QModelIndex&)));
  connect(filterBox, SIGNAL(textChanged(const QString&)),
          this, SLOT(refilterResults(const QString&)));

  layout->addWidget(filterBox);
  layout->addWidget(filterResults);

  // TODO align to top

  this->setLayout(layout);
  fieldEditor = entry;
}

void TrackerFilter::setTracker(Tracker *newTracker)
{
  closeTracker();

  tracker = newTracker;
  refilterResults("");
}

void TrackerFilter::closeTracker()
{
  if (tracker)
  {
    // TODO also need to retrieve entry->trackedEntry
    tracker->close();
  }
}

void TrackerFilter::refilterResults(const QString &text)
{
  filterResults->setModel(tracker->getEntries(text));
  filterResults->setModelColumn(1);
}

void TrackerFilter::selectResult(const QModelIndex& index)
{
  // TODO do we need to do this casting stuff?
  const QAbstractItemModel *model = index.model();
  const QSqlTableModel *table = dynamic_cast<const QSqlTableModel*>(model);
  QSqlRecord r = table->record(index.row());
  fieldEditor->setTrackedEntry(tracker->getEntry(r.value(0).toString()));
}
