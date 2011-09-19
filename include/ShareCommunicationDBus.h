/// \file
/// \brief This defines the dbus communication class.
/// \author Anthony Jaguenaud
/// \version v0.0
/// 
/// This file defines the class to communicate using dbus message bus.

#include "ShareCommunication.h"

namespace Share{
  /// \brief DBus communication class.
  class CommunicationDBus:public Communication
  {
  public:
    /// \brief Constructor.
    CommunicationDBus();
    /// \brief Destructor.
    virtual ~CommunicationDBus();
  };
};