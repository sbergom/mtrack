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
#include "filter.h"

TrackerFilter::TrackerFilter(EntryField *entry, QWidget *parent)
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
}

void TrackerFilter::refilterResults(const QString &text)
{
  // TODO
}

void TrackerFilter::selectResult(const QModelIndex&)
{
  // TODO
}
