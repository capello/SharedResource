/// \file
/// \brief This class store a unit of a Ressource using Communication class.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#include <ShareResourceStorageUnitCommunication.h>
#include <QtCore>
#include <ShareDebug.h>

Share::ResourceStorageUnitCommunication::ResourceStorageUnitCommunication(ResourceStorage::StorageMethod p_storageMethod)
{

  qWarning() << __func__ << "Not yet implemented.";
}

Share::ResourceStorageUnitCommunication::~ResourceStorageUnitCommunication()
{
  qWarning() << __func__ << "Not yet implemented.";
}

void Share::ResourceStorageUnitCommunication::storeData(QByteArray p_data)
{
  WHERE;
  if (getMode() != DATA)
    return;
  NOT_IMPLEMENTED;
}
