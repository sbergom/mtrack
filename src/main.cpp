#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QTextEdit>
#include <QDateEdit>
#include <QLineEdit>
#include <QMenuBar>
#include <QPushButton>
#include <QMenu>
#include "filter.h"
#include "entry.h"

QMenuBar* buildMainMenu(TrackerFilter *filter)
{
  QMenuBar *bar = new QMenuBar;
  QMenu *fileMenu = bar->addMenu("&File");
  QMenu *helpMenu = bar->addMenu("&Help");

  // TODO add menu
  fileMenu->addAction("&New");
  fileMenu->addAction("&Open");
  //fileMenu->addSeparator();
  // TODO recent files
  fileMenu->addSeparator();
  fileMenu->addAction("E&xit");

  helpMenu->addAction("Help");
  helpMenu->addAction("About");

  // TODO link all actions

  return bar;
}

QLayout* buildLayout()
{
  QVBoxLayout *wholeLayout = new QVBoxLayout;
  QHBoxLayout *field = new QHBoxLayout;

  EntryField *entry = new EntryField();
  TrackerFilter *filter = new TrackerFilter(entry);

  field->addWidget(filter);
  field->addWidget(entry);

  wholeLayout->addWidget(buildMainMenu(filter));
  wholeLayout->addLayout(field);
  
  // TODO connect panes together
  // TODO line between the panes?
  // TODO save on close

  return wholeLayout;
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // TODO parse out filename

  QWidget *window = new QWidget;
  window->setLayout(buildLayout());
  // TODO remove buffer to tightly fit into window
  // DISCUSS use QMainWindow instead
  window->show();

  return app.exec();
}
