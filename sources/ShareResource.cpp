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
  Resource::Config Resource::Config::instance;
  
  Resource::Resource()
  {
    std::cout << "const\n";
  }
  
  Resource::Resource(QByteArray &p_resource,Auth &p_owner)
  {
    // Get the resource storage.
    resource = ResourceStorage::getAnInstance();
    
    resource->setStorageMethod(Config::getInstance()->getStorageMethod());
      
    
    std::cout << "Const avec param\n";
  }
  
  Resource::Resource(Id p_resourceId)
  {
    qDebug() << "Construct resource by Id";
  }
  
  Resource::~Resource()
  {
    
    std::cout << "Dest\n";
  }
  
  
  Resource::Id Resource::getId()
  {
    return resourceId;
  }
  
  /////////////////////////////////////////////////////////
  // Config Part
  /////////////////////////////////////////////////////////
  Resource::Config::Config()
  {
    isAdminMode = false;
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
    return storageMethod == ResourceStorage::LOCAL_CACHE;
  }
  
  void Resource::Config::setLocalStorage(bool p_isUserMethod)
  {
    if (p_isUserMethod)
      storageMethod = ResourceStorage::LOCAL_CACHE;
    else
    {
      // Search in Configuration the good storage method.
      //Configuration::getInstance()->getUserConfig()->getUseSystemConfig();
      Configuration *l_conf = Configuration::getInstance();
      if (isAdminMode)
      {
        storageMethod = static_cast<ResourceStorage::StorageMethod> (l_conf->getSystem_SystemCommunicationMode());
      }
      else
      {
        if (l_conf->getUser_UseSystemConfig())
        {
          storageMethod = static_cast<ResourceStorage::StorageMethod> (l_conf->getSystem_UserCommunicationMode());
        }
        else
        {
          storageMethod = static_cast<ResourceStorage::StorageMethod> (l_conf->getUser_UserCommunicationMode());
        }
      }
      std::cerr << "<" << __func__ << "> not yet implemented\n";
    }
  }
  
  ResourceStorage::StorageMethod Resource::Config::getStorageMethod()
  {
    return storageMethod;
  }
  
  
  Resource::Config *Resource::Config::getInstance()
  {
    return &instance;
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