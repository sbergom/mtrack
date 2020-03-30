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

};

#endif // ENTRY_H
