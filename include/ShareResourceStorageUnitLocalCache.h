/// \file
/// \brief This class store a unit of a Ressource using local storage.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#ifndef __SHARE_RESOURCE_STORAGE_UNIT_LOCAL_CACHE
#define __SHARE_RESOURCE_STORAGE_UNIT_LOCAL_CACHE
#include "ShareResourceStorageUnit.h"

namespace Share
{
  class ResourceStorageUnitLocalCache:public ResourceStorageUnit
  {
  public:
    /// \brief Constructor
    ResourceStorageUnitLocalCache();

    /// \brief Destructor
    virtual ~ResourceStorageUnitLocalCache();

    /// \brief Add data to storage unit.
    /// \param[in] p_data Data to add.
    virtual void storeData(QByteArray p_data);

  };
};

#endif