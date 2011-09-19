/// \file
/// \brief Share communication provides internal communication.
/// \author Anthony Jaguenaud
/// \version v0.0
///
/// This file provides a communication service between clients. The class ShareCommunication 
/// define here is an abstract class.

namespace Share {
  /// \brief High level communication class.
  class Communication {
  public:
    /// \brief Constructor
    Communication();
    virtual ~Communication();
    
    /// \brief Send a message to an other peer.
    /// \param[in] p_share_message Share message to send.
    /// \return \arg \b True Message sent.
    ///         \arg \b False An error occur sending the message.
    virtual bool send(Message & p_share_message)=0;
    
    /// \brief Select the peer to communicate.
    /// \param[in] p_share_peer The peer to which communicate.
    /// \return \arg \b True Connected to peer.
    ///         \arg \b False Not connected.
    bool connectToPeer(Peer & p_share_peer);
  private:
    Peer peer;
  };
};
