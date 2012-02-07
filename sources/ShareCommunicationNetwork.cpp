/// \file
/// \brief Implementation of network communication class.
/// \author Anthony Jaguenaud
/// \version v0.1.0
#include <ShareCommunicationNetwork.h>

const int Share::CommunicationNetwork::s_minAdminPortNumber = 1;
const int Share::CommunicationNetwork::s_minUserPortNumber = 1024;
const int Share::CommunicationNetwork::s_maxPortNumber = 65535;
const int Share::CommunicationNetwork::s_defaultAdminPortNumber = 900;
const int Share::CommunicationNetwork::s_defaultUserPortNumber = 28000;
