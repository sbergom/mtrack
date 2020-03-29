#include "tracker.h"

TrackedEntry::TrackedEntry(QString id)
{
  if (id == "")
  {
    // TODO initialize defaults
  }
  else
  {
    // TODO read from stream
  }
}

TrackedEntry::~TrackedEntry()
{
  cancelEntry();
  // TODO free resources
}

void TrackedEntry::cancelEntry()
{
  // TODO
}

void TrackedEntry::saveEntry()
{
  // TODO
}

Tracker::Tracker()
{
}

Tracker::Tracker(QString filename)
{
  // TODO 
}

Tracker::~Tracker()
{
  this->close();
  // TODO free resources
}

void Tracker::close()
{
  // TODO 
}

void Tracker::getEntries(QString filter)
{
  // TODO
}

TrackedEntry* Tracker::getEntry(QString id)
{
  // TODO
  return nullptr;
}

TrackedEntry* Tracker::newTrackedEntry()
{
  // TODO
  return nullptr;
}

bool Tracker::needsUpdating()
{
  // TODO
  return false;
}

bool Tracker::updateSchema()
{
  // TODO
  return false;
}

QString Tracker::getMetaData(QString property)
{
  // TODO 
}
