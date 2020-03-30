#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QApplication>

#include "window.h"

TrackerWindow::TrackerWindow()
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
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QMenu *helpMenu = menuBar()->addMenu("&Help");
  QAction *qa;

  fileMenu->addAction("&New")->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
  // TODO action close any open files, create new one
  fileMenu->addAction("&Open")->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  // TODO action file selector, if success, close files and open new
  //fileMenu->addSeparator();
  // TODO recent files
  fileMenu->addSeparator();
  qa = fileMenu->addAction("E&xit");
  qa->setShortcuts(QKeySequence::Quit);
  connect(qa, &QAction::triggered, this, &QApplication::quit);
  // TODO action modal save, close files and exit

  helpMenu->addAction("Help")->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
  // TODO action modal dialog "Figure it out yourself!"
  helpMenu->addAction("About");
  // TODO action modal about dialog
}
