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
#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QWidget>

#include "entry.h"
#include "filter.h"

/*!
   \class TrackerWindow
   \brief The TrackerWindow represents the main interacting window.

   The TrackerWindow keeps track of all widgets and data entry used in
   the Movie List Tracker application.  All interface elements
   originate from here and all file handling is coordinated from this
   point.
 */
class TrackerWindow : public QMainWindow
{
  Q_OBJECT;
public:
  explicit TrackerWindow(QWidget *parent = nullptr);

  /*!
    \fn void TrackerWindow::loadTracker(const QString &trackerFile)

    Load the selected file to be tracked and coordinate any errors or
    needs for updating the schema with the user.
   */
  void loadTracker(const QString &trackerFile);

private:
  EntryField *entry;
  TrackerFilter *filter;

  void buildMainMenu();

signals:

public slots:
  /*!
    \fn void TrackerWindow::exitApplication()

    Coordinate the exiting of the application saving all data safely.
   */
  void exitApplication();

  /*!
    \fn void TrackerWindow::newTracker()

    Construct a new tracker file with a name supplied by the user and
    set it up as the currently edited file.
   */
  void newTracker();

  /*!
    \fn void TrackerWindow::loadTracker()

    Load a new tracker file specfied by a dialog box and set it up as
    the currently edited file.
   */
  void loadTracker();

  /*!
    \fn void TrackerWindow::aboutTracker()

    Display an "About Movie List Tracker" dialog box.
   */
  void aboutTracker();

  /*!
    \fn void TrackerWindow::helpTracker()

    Display helpful information on using the Movie List Tracker.
   */
  void helpTracker();
};

#endif // WINDOW_H
