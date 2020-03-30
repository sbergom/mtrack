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
  date = new QDateEdit;
  comments = new QTextEdit;

  form->addRow("Title", title);
  form->addRow("Notes", notes);
  form->addRow("Date", date);
  form->addRow("Comments", comments);

  saveButton = new QPushButton("Save");
  cancelButton = new QPushButton("Cancel");
  buttons->addWidget(cancelButton);
  buttons->addWidget(saveButton);
  // TODO align right

  // TODO connect all buttons

  layout->addLayout(form);
  layout->addLayout(buttons);

  this->setLayout(layout);
}
