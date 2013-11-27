/// \file
/// \brief Implement Resource storage class for Authentification
/// \author Anthony Jaguenaud
/// \version v0.1.0
///
#include <ShareResourceStorageMeta.h>
#include <ShareDebug.h>


Share::ResourceStorageMeta::ResourceStorageMeta()
{
}

Share::ResourceStorageMeta::~ResourceStorageMeta()
{
}

void Share::ResourceStorageMeta::addAMetaUnit(ResourceStorageUnit &p_storageUnit)
{
  m_resourceUnit.push_back(&p_storageUnit);
  p_storageUnit.setMeta(true);
}

void Share::ResourceStorageMeta::add(ResourceStorageUnit &p_storageUnit)
{
  m_resourceUnit.push_back(&p_storageUnit);
}

void Share::ResourceStorageMeta::flush()
{
  NOT_IMPLEMENTED;
}
