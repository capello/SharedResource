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
}