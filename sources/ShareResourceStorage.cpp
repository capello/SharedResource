/// \file
/// \brief Implement Resource storage class
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the Resource storage class witch is the interface class.
#include <ShareResourceStorage.h>
#include <ShareConfiguration.h>
#include <ShareResourceStorageUnitLocalCache.h>
#include <ShareResourceStorageUnitCommunication.h>
#include <ShareDebug.h>

namespace Share
{
  const qint64 ResourceStorage::s_defaultUnitSize = 64 * 1024;
  const ResourceStorage::StorageMethod ResourceStorage::s_defaultStorageMethod = ResourceStorage::UNKNOWN;

  ResourceStorage::StorageMethod ResourceStorage::s_storageMethod = ResourceStorage::s_defaultStorageMethod;
  qint64 ResourceStorage::s_unitSize = ResourceStorage::s_defaultUnitSize;
  QList<ResourceStorage*> ResourceStorage::s_listOfinstances;

  ResourceStorage::ResourceStorage()
  {
    // Add instance on list of instance of storages.
    s_listOfinstances.push_back(this);
  }

  ResourceStorage::~ResourceStorage()
  {
    s_listOfinstances.removeOne(this);
  }

  void ResourceStorage::setStorageMethod(ResourceStorage::StorageMethod p_storageMethod)
  {
    s_storageMethod = p_storageMethod;
  }

  ResourceStorage::StorageMethod ResourceStorage::getStorageMethod()
  {
    return s_storageMethod;
  }

  ResourceStorage* ResourceStorage::getAnInstance()
  {
    return new ResourceStorage;
  }

  void ResourceStorage::setOwner(Auth &p_auth)
  {
    qWarning() << __func__ << "Not yet implemented.";
  }

  void ResourceStorage::store(QByteArray & p_rawResource)
  {
    WHERE;
    if (m_units.size() == 0)
    {
      // This is a new resource.
      qint64 l_metaUnitNumber = newStorageUnit();
      // Associate the meta to the new storage unit.
      m_meta.add(*m_units.at(l_metaUnitNumber));
    }
    QByteArray l_rawResource;
    if (getEncrypted())
    {
      NOT_IMPLEMENTED;
      l_rawResource = p_rawResource;
    }
    else
    {
      l_rawResource = p_rawResource;
    }

    QByteArray l_leftPart;
    QByteArray l_rightPart;
    // If need multi part, loop for all part.
    while (l_rawResource.size() > s_unitSize)
    {
      qint64 l_currentUnitNumber = newStorageUnit();
      ResourceStorageUnit *l_currentUnit = m_units.at(l_currentUnitNumber);
      int l_size = l_rawResource.size();
      qDebug() << "l_size = " << l_size;
      // Copy a block into the new unit.
      //m_meta.
      l_leftPart = l_rawResource.left(s_unitSize - 1);
      l_rightPart = l_rawResource.right(l_size - s_unitSize);
      l_currentUnit->storeData(l_leftPart);
      // Add the current unit to meta data.
      m_meta.add(*l_currentUnit);

      l_rawResource = l_rightPart;
    }
    qDebug() << "l_size = " << l_rawResource.size();
    //
    qint64 l_currentUnitNumber = newStorageUnit();
    ResourceStorageUnit *l_currentUnit = m_units.at(l_currentUnitNumber);
    l_currentUnit->storeData(l_rawResource);
  }

  qint64 ResourceStorage::newStorageUnit()
  {
    ResourceStorageUnit *l_resourceStorageUnit;
    qint64 l_position;
    if (s_storageMethod == LOCAL_CACHE)
    {
      l_resourceStorageUnit = new ResourceStorageUnitLocalCache();
    }
    else
    {
      l_resourceStorageUnit = new ResourceStorageUnitCommunication(s_storageMethod);
    }
    l_position = m_units.size();
    m_units.push_back(l_resourceStorageUnit);
    return l_position;
  }

  void ResourceStorage::setPublic(bool p_isPublic)
  {
    m_isPublic = p_isPublic;
  }

  void ResourceStorage::setEncrypted(bool p_isEncrypted)
  {
    m_isEncrypted = p_isEncrypted;
  }

  bool ResourceStorage::getPublic()
  {
    return m_isPublic;
  }

  bool ResourceStorage::getEncrypted()
  {
    return m_isEncrypted;
  }

  void ResourceStorage::flush ()
  {
    // First flush meta.
    m_meta.flush();
    // Flush all units.
    for (QList< ResourceStorageUnit* >::const_iterator l_unit = m_units.begin(); l_unit != m_units.end(); ++l_unit)
    {
      (*l_unit)->flush();
    }
  }
};