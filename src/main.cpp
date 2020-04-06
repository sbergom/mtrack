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
#include <QApplication>
#include "window.h"
#include "tracker.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  TrackerWindow *window = new TrackerWindow();
  window->show();

  // Parse out a filename to load immediately.  Don't need any fancy
  // argument parsing at this time since we only have one argument.
  for (int i=0; i<argc; i++)
  {
    if (strcmp(argv[i], "-f") == 0)
    {
      if (++i < argc)
      {
        window->loadTracker(argv[i]);
      }
    }
  }

  return app.exec();
}
