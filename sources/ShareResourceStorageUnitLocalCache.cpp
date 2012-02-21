/// \file
/// \brief This class store a unit of a Ressource in local disk cache.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#include <QtCore>
#include <ShareResourceStorageUnitLocalCache.h>
  #include <ShareDebug.h>

Share::ResourceStorageUnitLocalCache::ResourceStorageUnitLocalCache()
{
  NOT_IMPLEMENTED;
}

Share::ResourceStorageUnitLocalCache::~ResourceStorageUnitLocalCache()
{
  NOT_IMPLEMENTED;
}

void Share::ResourceStorageUnitLocalCache::storeData(QByteArray p_data)
{
  WHERE;
  if (getMode() != DATA)
    return;

  NOT_IMPLEMENTED;
}
