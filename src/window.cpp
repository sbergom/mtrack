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
#include <QAction>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>

#include "window.h"

TrackerWindow::TrackerWindow(QWidget *parent) : QMainWindow(parent)
{
  setWindowTitle("Movie Tracker");
  resize(650, 400);

  QHBoxLayout *field = new QHBoxLayout;

  entry = new EntryField();
  filter = new TrackerFilter(entry);

  field->addWidget(filter);
  field->addWidget(entry);

  QLabel *mainWidget = new QLabel;
  mainWidget->setLayout(field);

  buildMainMenu();

  setCentralWidget(mainWidget);
}

void TrackerWindow::buildMainMenu()
{
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction *qa;

  qa = fileMenu->addAction(tr("&New"));
  qa->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
  connect(qa, SIGNAL(triggered()), this, SLOT(newTracker()));

  qa = fileMenu->addAction(tr("&Open"));
  qa->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  connect(qa, SIGNAL(triggered()), this, SLOT(loadTracker()));

  //fileMenu->addSeparator();
  // TODO recent files

  fileMenu->addSeparator();

  qa = fileMenu->addAction(tr("E&xit"));
  qa->setShortcuts(QKeySequence::Quit);
  connect(qa, SIGNAL(triggered()), this, SLOT(exitApplication()));

  qa = helpMenu->addAction(tr("Help"));
  qa->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
  connect(qa, SIGNAL(triggered()), this, SLOT(helpTracker()));

  qa = helpMenu->addAction(tr("About"));
  connect(qa, SIGNAL(triggered()), this, SLOT(aboutTracker()));
}

void TrackerWindow::exitApplication()
{
  filter->closeTracker();
  qApp->quit();
}

void TrackerWindow::newTracker()
{
  QFileDialog dialog(this,
                     tr("New Movie Tracker"),
                     "",
                     tr("Tracker Files (*.trk)"));
  dialog.setAcceptMode(QFileDialog::AcceptSave);
  if (dialog.exec())
  {
    QString trackerFile = dialog.selectedFiles().at(0);
    Tracker *newTracker = new Tracker(trackerFile);
    if (newTracker->hasError())
    {
      QMessageBox::critical(this,
                            tr("Error opening tracker"),
                            newTracker->getLastError());
      delete newTracker;
    }
    else
    {
      filter->setTracker(newTracker);
    }
  }
}

void TrackerWindow::loadTracker()
{
  QString trackerFile = QFileDialog::getOpenFileName(this,
    tr("Open Movie Tracker"), "", tr("Tracker Files (*.trk)"));
  loadTracker(trackerFile);
}

void TrackerWindow::loadTracker(const QString &trackerFile)
{
  Tracker *newTracker = new Tracker(trackerFile);
  if (newTracker->needsUpdating())
  {
    QMessageBox::StandardButton result =
      QMessageBox::question(this, tr("Tracker needs updating"),
                            tr("The tracker file was made using an older "
                               "version of this program and needs updating. "
                               "Do you want to update the file now?"));
    if (result == QMessageBox::Yes)
    {
      newTracker->updateSchema();
    }
  }

  if (newTracker->hasError())
  {
    QMessageBox::critical(this,
                          tr("Error opening tracker"),
                          newTracker->getLastError());
    delete newTracker;
  }
  else
  {
    filter->setTracker(newTracker);
  }
}

void TrackerWindow::aboutTracker()
{
  QMessageBox::about(this,
                     tr("About"),
                     tr("Movie List Tracker"
                        "<p>Copyright &copy; 2020 Steven Bergom.  "
                        "This is an application to keep track of movies and "
                        "other media you want to experience."));
}

void TrackerWindow::helpTracker()
{
  QMessageBox::information(this,
                           tr("You need help?"),
                           tr("Figure it out yourself!"));
}
