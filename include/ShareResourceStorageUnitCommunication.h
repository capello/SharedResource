/// \file
/// \brief This class store a unit of a Ressource uning communication to store remotly.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#ifndef __SHARE_RESOURCE_STORAGE_UNIT_H
#define __SHARE_RESOURCE_STORAGE_UNIT_H

#include "ShareResourceStorageUnit.h"
#include "ShareResourceStorage.h"

namespace Share
{
  class ResourceStorageUnitCommunication:public ResourceStorageUnit
  {
  public:
    /// \brief Constructor.
    ResourceStorageUnitCommunication(ResourceStorage::StorageMethod p_storageMethod);

    /// \brief Destructor.
    virtual ~ResourceStorageUnitCommunication();

    /// \brief Add data to storage unit.
    /// \param[in] p_data Data to add.
    virtual void storeData(QByteArray p_data);

  };
};

#endif