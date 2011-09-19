/// \file
/// \brief Defines a message for communication in share cloud.
/// \author Anthony Jaguenaud
/// \version v0.0
///
/// Message defines the different kind of message to global communication.
/// The communication could be local or through network.

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