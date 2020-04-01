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
#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "entry.h"
#include "filter.h"

class TrackerWindow : public QMainWindow
{
  Q_OBJECT;
public:
  explicit TrackerWindow(QWidget *parent = nullptr);
  
private:
  EntryField *entry;
  TrackerFilter *filter;

  void buildMainMenu();

signals:

public slots:
  void exitApplication();
  void newTracker();
  void loadTracker();
  void aboutTracker();
  void helpTracker();
};

#endif // WINDOW_H
