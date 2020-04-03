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
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "entry.h"
#include "filter.h"

EntryField::EntryField(QWidget *parent) : QWidget(parent)
{
  QVBoxLayout *layout = new QVBoxLayout;
  QFormLayout *form = new QFormLayout;
  QHBoxLayout *buttons = new QHBoxLayout;

  title = new QLineEdit;
  notes = new QLineEdit;
  date = new QLineEdit;
  comments = new QTextEdit;

  form->addRow("Title", title);
  form->addRow("Notes", notes);
  form->addRow("Date", date);
  form->addRow("Comments", comments);

  deleteButton = new QPushButton("Delete");
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteTrackedEntry()));

  saveButton = new QPushButton("Save");
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveTrackedEntry()));

  cancelButton = new QPushButton("Cancel");
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelTrackedEntry()));

  // TODO disable buttons until data has changed

  buttons->addWidget(deleteButton);
  buttons->addWidget(cancelButton);
  buttons->addWidget(saveButton);
  // TODO align right

  layout->addLayout(form);
  layout->addLayout(buttons);

  this->setLayout(layout);
  entry = nullptr;
}

void EntryField::setTrackedEntry(TrackedEntry *entry)
{
  if (this->entry)
  {
    this->entry->cancelEntry();
  }

  this->entry = entry;
  title->setText(entry->getName());
  notes->setText(entry->getNote());
  //date->setText(entry->getDate().toString());
  date->setText(entry->getDate());
  comments->setText(entry->getComment());
}

void EntryField::closeTrackedEntry()
{
  if (entry)
  {
    entry->cancelEntry();
  }
}

void EntryField::deleteTrackedEntry()
{
  if (entry)
  {
    entry->deleteEntry();
    entry = nullptr;
    filter->newTrackedEntry();

    filter->refilterResults(filter->getFilterText());
  }
}

void EntryField::saveTrackedEntry()
{
  entry->setName(title->text());
  entry->setNote(notes->text());
  //entry->setDate(QDate::fromString(date->text()));
  entry->setDate(date->text());
  entry->setComment(comments->toPlainText());

  entry->saveEntry();

  filter->refilterResults(filter->getFilterText());
}

void EntryField::cancelTrackedEntry()
{
  title->setText(entry->getName());
  notes->setText(entry->getNote());
  //date->setText(entry->getDate().toString());
  date->setText(entry->getDate());
  comments->setText(entry->getComment());
}
