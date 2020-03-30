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
  // TODO onclick trackedEntry.save()
  cancelButton = new QPushButton("Cancel");
  // TODO onclick revert trackedEntry
  buttons->addWidget(newButton);
  buttons->addWidget(cancelButton);
  buttons->addWidget(saveButton);
  // TODO align right

  layout->addLayout(form);
  layout->addLayout(buttons);

  this->setLayout(layout);
}
