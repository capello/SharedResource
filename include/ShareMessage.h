/// \file
/// \brief Defines a message for communication in share cloud.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// Message defines the different kind of message to global communication.
/// The communication could be local or through network.

#ifndef __SHARE_MESSAGE_H
#define __SHARE_MESSAGE_H

namespace Share {
  /// \brief The high level message class.
  class Message {
  public:
    /// \brief Constructor.
    Message();
    /// \brief Destructor.
    virtual ~Message();
    
  private:
  };
};

#endif
