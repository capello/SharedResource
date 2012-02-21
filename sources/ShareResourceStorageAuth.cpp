/// \file
/// \brief Implement Resource storage class for Authentification
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
#include <ShareResourceStorageAuth.h>


Share::ResourceStorageAuth::ResourceStorageAuth()
{
}

Share::ResourceStorageAuth::~ResourceStorageAuth()
{
}

void Share::ResourceStorageAuth::add(ResourceStorageUnit &p_storageUnit)
{
  m_resourceUnit.push_back(&p_storageUnit);
  p_storageUnit.setMeta(true);
}
