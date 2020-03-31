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
#ifndef ENTRY_H
#define ENTRY_H

#include <QDateEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "tracker.h"

class EntryField : public QWidget
{
  Q_OBJECT;
public:
  explicit EntryField(QWidget *parent = nullptr);

  void setTrackedEntry(TrackedEntry *entry);

private:
  QLineEdit *title;
  QLineEdit *notes;
  QLineEdit *date;
  QTextEdit *comments;
  QPushButton *newButton;
  QPushButton *saveButton;
  QPushButton *cancelButton;
  TrackedEntry *entry;
  
signals:

public slots:
  void saveTrackedEntry();
  void cancelTrackedEntry();

};

#endif // ENTRY_H
