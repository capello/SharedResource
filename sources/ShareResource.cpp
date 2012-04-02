/// \file
/// \brief Implement Resource class
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the Resource class witch is the interface class.

#include <ShareResource.h>
#include <iostream>
#include <ShareConfiguration.h>

namespace Share
{
  Resource::Config Resource::Config::s_instance;

  Resource::Resource()
  {
    std::cout << "const\n";
  }

  Resource::Resource(QByteArray &p_resource, Auth *p_owner)
  {
    // Get the resource storage.
    m_storage = ResourceStorage::getAnInstance();

    // Set the storageMethod.
    m_storage->setStorageMethod(Config::getInstance()->getStorageMethod());

    // Set owner

    if (p_owner != NULL)
    {
      m_owner = p_owner;
    }
    else
    {
      m_owner = Config::getInstance()->getOwnerByDefault();
    }

    m_storage->setOwner(*m_owner);

    // If owner if default value, public and encrypted are set to false.
    if (*m_owner == Auth::Undefine)
    {
      m_storage->setPublic(true);
      m_storage->setEncrypted(false);
    }
    else
    {
      m_storage->setPublic(Config::getInstance()->getPublicByDefault());
      m_storage->setEncrypted(Config::getInstance()->getEncryptedByDefault());
    }

    m_storage->store(p_resource);

    std::cout << "Const avec param\n";
  }

  Resource::Resource(Id p_resourceId)
  {
    qDebug() << "Construct resource by Id";
  }

  Resource::~Resource()
  {
    if (m_storage != NULL)
      m_storage->flush();

    std::cout << "Dest\n";
  }


  Resource::Id Resource::getId()
  {
    return m_resourceId;
  }

  /////////////////////////////////////////////////////////
  // Config Part
  /////////////////////////////////////////////////////////
  Resource::Config::Config()
  {
    m_isAdminMode = false;
    m_isEncryptedByDefault = true;
    m_isPublicByDefault = false;
    m_defaultOwner = &Auth::Undefine;
    if (!Configuration::getInstance()->readConf())
    {
      // Load config file failed.
      setLocalStorage(true);
    }
  }

  Resource::Config::~Config()
  {
  }

  bool Resource::Config::isLocalStorage() const
  {
    return m_storageMethod == ResourceStorage::LOCAL_CACHE;
  }

  void Resource::Config::setLocalStorage(bool p_isUserMethod)
  {
    if (p_isUserMethod)
      m_storageMethod = ResourceStorage::LOCAL_CACHE;
    else
    {
      // Search in Configuration the good storage method.
      //Configuration::getInstance()->getUserConfig()->getUseSystemConfig();
      Configuration *l_conf = Configuration::getInstance();
      if (m_isAdminMode)
      {
        m_storageMethod = static_cast<ResourceStorage::StorageMethod> (l_conf->getSystem_SystemCommunicationMode());
      }
      else
      {
        if (l_conf->getUser_UseSystemConfig())
        {
          m_storageMethod = static_cast<ResourceStorage::StorageMethod> (l_conf->getSystem_UserCommunicationMode());
        }
        else
        {
          m_storageMethod = static_cast<ResourceStorage::StorageMethod> (l_conf->getUser_UserCommunicationMode());
        }
      }
      std::cerr << "<" << __func__ << "> not yet implemented\n";
    }
  }

  ResourceStorage::StorageMethod Resource::Config::getStorageMethod()
  {
    return m_storageMethod;
  }


  Resource::Config *Resource::Config::getInstance()
  {
    return &s_instance;
  }

  /// \TODO To implements. if load is true, set manual Modified to false.
  bool Resource::Config::loadConfigFile()
  {
    return false;
  }

  /// \TODO To implements.
  bool Resource::Config::saveConfigFile() const
  {
    return false;
  }
  void Resource::Config::setPublicByDefault(bool p_isPublic)
  {
    m_isPublicByDefault = p_isPublic;
  }

  bool Resource::Config::getPublicByDefault()
  {
    return m_isPublicByDefault;
  }

  void Resource::Config::setEncryptedByDefault(bool p_isEncrypted)
  {
    m_isEncryptedByDefault = p_isEncrypted;
  }

  bool Resource::Config::getEncryptedByDefault()
  {
    return m_isEncryptedByDefault;
  }

  void Resource::Config::setOwnerByDefault(Auth * p_owner)
  {
    m_defaultOwner = p_owner;
  }

  Auth * Resource::Config::getOwnerByDefault()
  {
    return m_defaultOwner;
  }

  //////////////////////////////////////////////////////////////////////
  /////// Resource Id part
  //////////////////////////////////////////////////////////////////////
  Resource::Id::Id()
  {
  }

  Resource::Id::~Id()
  {
  }

}