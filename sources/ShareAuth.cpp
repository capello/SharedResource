/// \file
/// \brief Implementation of Auth class.
/// \author Anthony Jaguenaud
/// \version v0.1.0

#include "ShareAuth.h"

#warning Auth class is not shure for the moment.

namespace Share {
  
  int Auth::auth_number = 0;
  Auth Auth::Undefine;
  Auth::Auth()
  {
    auth = auth_number++;
  }
  
  Auth::~Auth()
  {
  }
  
  bool Auth::operator == (Auth & p_auth)
  {
    return auth == p_auth.auth;
  }
};
