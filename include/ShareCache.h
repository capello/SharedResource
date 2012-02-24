/// \file
/// \brief This class implements the cache setting and control class.
///

#ifndef __SHARE_CACHE_H
#define __SHARE_CACHE_H

#include <QtCore>

namespace Share
{
  class Cache
  {
  public:
    /// \brief Get the singleton instance.
    /// \return \b Cache singletonk
    static Cache &getInstance();

    /// \brief Refresh cache values.
    void refresh();

    /// \brief Get free space.
    /// \return \b Free \b space available in current cache.
    qint64 getFreeSpace();


  private:
    /// \brief Constructor
    Cache();
    /// \brief Destructor
    ~Cache();

    /// \brief The boolean if used to refresh values if changed have been done.
    bool m_hasChanged;
    /// \brief The cache size value.
    qint64 m_cacheSize;
    /// \brief The cache used value.
    qint64 m_cacheUsed;
    /// \brief The cache free value.
    qint64 m_cacheFree;
    /// \brief The real disk usage.
    qint64 m_diskFree;
    static Cache s_instance;

  };
};

#endif
