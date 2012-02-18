/// \file
/// \brief Implement Resource storage class
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the Resource storage class witch is the interface class.
#include <ShareResourceStorage.h>
#include <ShareConfiguration.h>

namespace Share
{
  ResourceStorage::StorageMethod ResourceStorage::s_storage_method;
  qint64 ResourceStorage::s_cacheSize;
  qint64 ResourceStorage::s_cacheUsed;
  qint64 ResourceStorage::s_cacheFree;
  qint64 ResourceStorage::s_unitSize;
  QList<ResourceStorage*> ResourceStorage::s_listOfinstances;

  ResourceStorage::ResourceStorage()
  {
    s_listOfinstances.push_back(this);
  }

  ResourceStorage::~ResourceStorage()
  {
    s_listOfinstances.removeOne(this);
  }

  void ResourceStorage::setStorageMethod(ResourceStorage::StorageMethod p_storageMethod)
  {
    s_storage_method = p_storageMethod;
  }

  ResourceStorage::StorageMethod ResourceStorage::getStorageMethod()
  {
    return s_storage_method;
  }

  ResourceStorage* ResourceStorage::getAnInstance()
  {
    return new ResourceStorage;
  }

  void ResourceStorage::setOwner(Auth p_auth)
  {
    qWarning() << __func__ << "Not yet implemented.";
  }

  void ResourceStorage::store(QByteArray & p_rawResource)
  {
    qWarning() << __func__ << "Not yet implemented.";
  }

};