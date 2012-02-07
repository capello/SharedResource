/// \file
/// \brief This defines the share mom communication class.
/// \author Anthony Jaguenaud
/// \version v0.1.0
/// 
/// This file defines the class to communicate using share memory.

#ifndef __SHARE_COMMUNICATION_SHARE_MEM_H
#define __SHARE_COMMUNICATION_SHARE_MEM_H

#include "ShareCommunication.h"

namespace Share{
  /// \brief Share memory communication class.
  class CommunicationShareMem:public Communication
  {
  public:
    /// \brief Constructor.
    CommunicationShareMem();
    /// \brief Destructor.
    virtual ~CommunicationShareMem();
  };
};
#endif
