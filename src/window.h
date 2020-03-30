#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "entry.h"
#include "filter.h"

class TrackerWindow : public QMainWindow
{
  Q_OBJECT;
public:
  explicit TrackerWindow();
  
private:
  EntryField *entry;
  TrackerFilter *filter;

  void buildMainMenu();

signals:

public slots:

};

#endif // WINDOW_H
