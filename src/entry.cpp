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

EntryField::EntryField(QWidget *parent)
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

  newButton = new QPushButton("New");
  // TODO onclick clear filterReults.select, create new TrackedEntry, update this
  saveButton = new QPushButton("Save");
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveTrackedEntry()));

  cancelButton = new QPushButton("Cancel");
  connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelTrackedEntry()));

  // TODO disable buttons until data has changed

  buttons->addWidget(newButton);
  buttons->addWidget(cancelButton);
  buttons->addWidget(saveButton);
  // TODO align right

  layout->addLayout(form);
  layout->addLayout(buttons);

  this->setLayout(layout);
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
  date->setText(entry->getDate().toString());
  comments->setText(entry->getComment());
}

void EntryField::saveTrackedEntry()
{
  // TODO can we assume entry is not null?
  entry->setName(title->text());
  entry->setNote(notes->text());
  entry->setDate(QDate::fromString(date->text()));
  entry->setComment(comments->toPlainText());
}

void EntryField::cancelTrackedEntry()
{
  // TODO can we assume entry is not null?
  title->setText(entry->getName());
  notes->setText(entry->getNote());
  date->setText(entry->getDate().toString());
  comments->setText(entry->getComment());
}
