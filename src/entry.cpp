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
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
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

  form->addRow(tr("Title"), title);
  form->addRow(tr("Notes"), notes);
  form->addRow(tr("Date"), date);
  form->addRow(tr("Comments"), comments);

  connect(title, SIGNAL(textChanged(const QString&)),
          this, SLOT(entryModified(const QString&)));
  connect(notes, SIGNAL(textChanged(const QString&)),
          this, SLOT(entryModified(const QString&)));
  connect(date, SIGNAL(textChanged(const QString&)),
          this, SLOT(entryModified(const QString&)));
  connect(comments, SIGNAL(textChanged()),
          this, SLOT(entryModified()));

  deleteButton = new QPushButton(tr("Delete"));
  connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteTrackedEntry()));

  saveButton = new QPushButton(tr("Save"));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveTrackedEntry()));

  cancelButton = new QPushButton(tr("Cancel"));
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

  hasModifications = false;
  saveButton->setEnabled(false);
  cancelButton->setEnabled(false);
  deleteButton->setEnabled(false);
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

  hasModifications = false;
  saveButton->setEnabled(false);
  cancelButton->setEnabled(false);
  if (entry->getID() != MTRACK_NEWENTRY_ID)
  {
    deleteButton->setEnabled(true);
  }
  else
  {
    deleteButton->setEnabled(false);
  }
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

    hasModifications = false;
    saveButton->setEnabled(false);
    cancelButton->setEnabled(false);
    deleteButton->setEnabled(false);
  }
}

void EntryField::saveTrackedEntry()
{
  if (title->text() == "")
  {
    QMessageBox::information(nullptr,
                             "No Title",
                             "You must provide a title before saving.");
    return;
  }
  entry->setName(title->text());
  entry->setNote(notes->text());
  //entry->setDate(QDate::fromString(date->text()));
  entry->setDate(date->text());
  entry->setComment(comments->toPlainText());

  entry->saveEntry();

  filter->refilterResults(filter->getFilterText());

  hasModifications = false;
  saveButton->setEnabled(false);
  cancelButton->setEnabled(false);
  deleteButton->setEnabled(true);
}

void EntryField::cancelTrackedEntry()
{
  title->setText(entry->getName());
  notes->setText(entry->getNote());
  //date->setText(entry->getDate().toString());
  date->setText(entry->getDate());
  comments->setText(entry->getComment());

  hasModifications = false;
  saveButton->setEnabled(false);
  cancelButton->setEnabled(false);
  deleteButton->setEnabled(true);
}

void EntryField::entryModified(const QString &value)
{
  entryModified();
}

void EntryField::entryModified()
{
  if (!hasModifications)
  {
    hasModifications = true;
    saveButton->setEnabled(true);
    cancelButton->setEnabled(true);
  }
}
