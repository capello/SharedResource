/// \file
/// \brief This defines the network communication class.
/// \author Anthony Jaguenaud
/// \version v..
/// 
/// This file defines the class to communicate over network.

#ifndef __SHARE_COMMUNICATION_NETWORK_H
#define __SHARE_COMMUNICATION_NETWORK_H

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
    
    /// \brief Set address of the peer.
    /// \param[in] p_peer_addr IP address of peer.
    void setAddr(QHostAddress & p_peer_addr);
    
    /// \brief Constant for configuration usage.
    static const int s_minAdminPortNumber;
    
    /// \brief Constant for configuration usage.
    static const int s_minUserPortNumber;
    
    /// \brief Constant for configuration usage.
    static const int s_maxPortNumber;
    
    /// \brief Constant for configuration usage.
    static const int s_defaultAdminPortNumber;
    
    /// \brief Constant for configuration usage.
    static const int s_defaultUserPortNumber;
  };
};

#endif