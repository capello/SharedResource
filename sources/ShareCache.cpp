/// \file
/// \brief This file implements the Cache class.

#include <ShareCache.h>
#include <ShareDebug.h>

Share::Cache Share::Cache::s_instance;

Share::Cache::Cache()
{
  WHERE;
  // To calculate the cache size at the first access.
  m_hasChanged = true;
  m_cacheFree = -1;
  m_cacheSize = -1;
  m_diskFree  = -1;
  m_cacheUsed = -1;
  NOT_IMPLEMENTED;
}

Share::Cache::~Cache()
{
  WHERE;
}

Share::Cache & Share::Cache::getInstance()
{
  return s_instance;
}

void Share::Cache::refresh()
{
  WHERE;
  NOT_IMPLEMENTED;
}
