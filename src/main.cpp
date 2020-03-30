#include <QApplication>
#include "filter.h"
#include "entry.h"
#include "window.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // TODO parse out filename

  TrackerWindow *window = new TrackerWindow();
  window->show();

  return app.exec();
}
