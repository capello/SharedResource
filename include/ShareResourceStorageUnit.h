/// \file
/// \brief This class store a unit of a Ressource.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// A unit is a piece of.
/// For example is you have a unit size equal to 64MB, a ressource of 264MB will be 
/// separate into 5 units. Each unit will be replicated over the network.
/// This class can exists only if Share::ShareResourceStorage::s_storage_method == Share::StorageMethod::DISK

#ifndef __SHARE_RESSOURCE_STORAGE_UNIT_H
#define __SHARE_RESSOURCE_STORAGE_UNIT_H

#include <qfile.h>
#include <ShareResource.h>

namespace Share
{
  /// \brief Unit Storage class
  class ResourceStorageUnit
  {
  public:
    /// \brief Constructor.
    ResourceStorageUnit();
    /// \brief Destructor.
    virtual ~ResourceStorageUnit();
    
    /// \brief Don't remember usage
    /// \todo Complete doxygen brief description.
    bool isSafe();
    
    /// \brief Return resource id.
    /// \return The resource id of the resource which this is a part.
    Resource::Id getResourceId();
    
    /// \brief Return the part number.
    /// \return Return the number of the part of the resource.
    qint64 getPartNumber();
  private:
    qint64 sizeOfData;
    QFile associatedFile;
  };
};
#endif
