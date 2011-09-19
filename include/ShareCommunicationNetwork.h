/// \file
/// \brief This defines the network communication class.
/// \author Anthony Jaguenaud
/// \version v0.0
/// 
/// This file defines the class to communicate over network.

#include "ShareCommunication.h"

namespace Share{
  /// \brief Network communication class.
  class CommunicationNetwork:public Communication
  {
  public:
    /// \brief Constructor.
    CommunicationNetwork();
    /// \brief Destructor.
    virtual ~CommunicationNetwork();
  };
};