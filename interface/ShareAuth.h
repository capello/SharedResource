/// \file
/// \brief This file declares ShareAuth class.
/// \author Anthony Jaguenaud
/// \version v0.1.0
/// 
/// ShareAuth is a authentification class.
/// The class default class is a "yes" class. That mean, the class reply every time that authentification is good.
/// If you want your own class, you should derived this class.

#ifndef __SHARE_AUTH_H
#define __SHARE_AUTH_H

namespace Share {
  /// \brief Authentification class.
  class Auth
  {
  public:
    /// \brief Constructor.
    Auth();
    /// \brief Destructor.
    virtual ~Auth();
    
  private:
    
  };
};

#endif
