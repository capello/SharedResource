/// \file
/// \brief QCA authentification.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
/// The class QCAAuth is used to authentification using public keys.

#ifndef __SHARE_QCA_AUTH_H
#define __SHARE_QCA_AUTH_H

#include <ShareAuth.h>

namespace Share {
  /// \brief QCAAuth implements Auth using pgp or rsa algorithm for share resource library.
  class QCAAuth:public Auth {
  public:
    /// \brief Constructor.
    QCAAuth();
    /// \brief Destructor.
    virtual ~QCAAuth();
    
  };
};

#endif
