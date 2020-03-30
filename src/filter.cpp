#include <QVBoxLayout>
#include "filter.h"

TrackerFilter::TrackerFilter(EntryField *entry, QWidget *parent)
{
  QVBoxLayout *layout = new QVBoxLayout;

  filterBox = new QLineEdit;
  filterResults = new QListWidget;
  filterResults->setSelectionMode(QAbstractItemView::SingleSelection);

  layout->addWidget(filterBox);
  layout->addWidget(filterResults);

  // TODO align to top
  // TODO connect filterBox and filterResults

  this->setLayout(layout);
}
