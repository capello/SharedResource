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
#include <QByteArray>

namespace Share {
  /// \brief Authentification class.
  class Auth
  {
  public:
    /// \brief Constructor.
    Auth();
    /// \brief Destructor.
    virtual ~Auth();

    /// \brief operator ==
    /// Return if class represent the same object.
    /// \param[in] p_auth A authentification class to compare with \b this.
    /// \return \li \b true: It is the same object.
    ///         \li \b false: It is not the same object.
    bool operator == (Auth &p_auth);

    /// \brief Check if this is the good user.
    /// \param[in] p_chalenge The data encrypted with the public key.
    /// \return Data decrypted by the key of auth.
    QByteArray chalenge(QByteArray p_chalenge);

    static Auth Undefine;
  private:
    // \FIXME Bad code.
    static int auth_number;
    int auth;
  };
};

#endif
