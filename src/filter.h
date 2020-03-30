#ifndef FILTER_H
#define FILTER_H

#include <QLineEdit>
#include <QListWidget>
#include <QWidget>

#include "tracker.h"
#include "entry.h"

class TrackerFilter : public QWidget
{
  Q_OBJECT;
public:
  explicit TrackerFilter(EntryField *entry, QWidget *parent = nullptr);

private:
  QLineEdit *filterBox;
  QListWidget *filterResults;

signals:

public slots:

};

#endif // FILTER_H
