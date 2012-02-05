/// \file
/// \brief This file declares Peer class.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// This file declares the class use to manage peers.
/// A peer can be a local session deamon, or system deamon,
/// or a network address.

#include <QtNetwork/QHostAddress>
#include "ShareResource.h"
#include "ShareCommunication.h"


namespace Share
{
  /// \brief Peer class.
  class Peer
  {
  public:
    /// \brief Constructor.
    Peer();
    /// \brief Constructor.
    /// \param[in] p_peer_addr IP address of peer.
    /// \param[in] p_peer_auth Authentificate peer.
    Peer(QHostAddress & p_peer_addr, Auth p_peer_auth);
    
    /// \brief Destructor.
    virtual ~Peer();
    
    /// \brief Set authentificate of peer.
    /// \param[in] p_peer_auth Authentificate peer.
    void setAuth(Auth & p_peer_auth);
    
    /// \brief Open network connection with peer.
    void openConnection();
    
    /// \brief Close network connection with peer.
    void closeConnection();
    
    /// \brief return if the connection to peer is up.
    /// \return \li \b True if the connection to peer is up.
    ///         \li \b False if the connection to peer is closed.
    bool isConnectionOpened();
    
    /// \brief Send a resource to the peer.
    /// \param[in] p_resources Resource to send to peer.
    void sendResource(Resource & p_resources);
    
    /// \brief Getter of the communication class associated for the peer.
    /// \return Reference of communication class use to contact this peer.
    Communication & communicationGet() const;
    
  private:
    Auth peer_auth;
    Communication peer_communication;
  };
}
