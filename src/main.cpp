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

QMenuBar* buildMainMenu()
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

QLayout* buildSearchPane()
{
  QVBoxLayout *layout = new QVBoxLayout;
  QLineEdit *filterBox = new QLineEdit;
  QWidget *filterResults = new QLineEdit; // TODO replace

  layout->addWidget(filterBox);
  layout->addWidget(filterResults);

  // TODO align to top
  // TODO connect filterBox and filterResults

  return layout;
}

QLayout* buildEntryPane()
{
  QVBoxLayout *layout = new QVBoxLayout;
  QFormLayout *form = new QFormLayout;
  QHBoxLayout *buttons = new QHBoxLayout;

  form->addRow("Title", new QLineEdit());
  form->addRow("Notes", new QLineEdit());
  form->addRow("Date", new QDateEdit()); // TODO Initialize to today
  form->addRow("Comments", new QTextEdit());

  QPushButton *saveButton = new QPushButton("Save");
  QPushButton *cancelButton = new QPushButton("Cancel");
  buttons->addWidget(cancelButton);
  buttons->addWidget(saveButton);

  // TODO connect all buttons

  layout->addLayout(form);
  layout->addLayout(buttons);
  
  return layout;
}

QLayout* buildLayout()
{
  QVBoxLayout *wholeLayout = new QVBoxLayout;
  QHBoxLayout *field = new QHBoxLayout;

  field->addLayout(buildSearchPane());
  field->addLayout(buildEntryPane());

  wholeLayout->addWidget(buildMainMenu());
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
