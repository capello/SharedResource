/// \file
/// \brief Implement Resource class
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file implements the Resource class witch is the interface class.

#include <ShareResource.h>
#include <iostream>

namespace Share
{
  Resource::Resource()
  {
    std::cout << "const\n";
  }
  
  Resource::Resource(QByteArray &p_resource)
  {
    
    std::cout << "Const avec param\n";
  }
  
  Resource::~Resource()
  {
    std::cout << "Dest\n";
  }
  
  Resource::Config::Config()
  {
    if (!loadConfigFile())
    {
      canManuallyModify = true;
      // Load config file failed.
      setUserStorage(true);
    }
  }
  
  Resource::Config::~Config()
  {
  }
  
  bool Resource::Config::isUserStorage() const
  {
    return storageMethod.getStorageMethod();
  }
  
  void Resource::Config::setUserStorage(bool p_isUserMethod)
  {
    if (canManuallyModify)
      storageMethod.setStorageMethod(p_isUserMethod?Share::ResourceStorage::DISK:Share::ResourceStorage::DEAMON);
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
}