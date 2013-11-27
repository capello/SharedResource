/// \file
/// \brief This class store a unit of a Ressource in local disk cache.
/// \author Anthony Jaguenaud
/// \version v0.1.0
///

#include <QtCore>
#include <ShareResourceStorageUnitLocalCache.h>
  #include <ShareDebug.h>
#include <ShareConfiguration.h>
#include <ShareCache.h>
#include <qca_basic.h>

Share::ResourceStorageUnitLocalCache::ResourceStorageUnitLocalCache()
{
  NOT_IMPLEMENTED;
}

Share::ResourceStorageUnitLocalCache::~ResourceStorageUnitLocalCache()
{
  NOT_IMPLEMENTED;
}

void Share::ResourceStorageUnitLocalCache::storeData(QByteArray p_data)
{
  WHERE;
  if (getMode() != DATA)
    return;

  // Check destination dir.
  QDir l_destinationDir(Configuration::getInstance()->getCachePath());
  if (!l_destinationDir.exists())
  {
    qCritical("Cache directory “%s” does not exists.",Configuration::getInstance()->getCachePath().toStdString().c_str());
    return;
  }

  // Check quota
  qint64 l_freeSpace = Cache::getInstance().getFreeSpace();

  // Create file name
  QString l_fullFileName = l_destinationDir.absolutePath() + QString("/") + computeFileName(p_data);
  qDebug() << "full file name = " << l_fullFileName << l_fullFileName.lastIndexOf('/') << l_fullFileName.length();
  // Create directory if not exists.
  l_destinationDir.setPath(l_fullFileName.left(l_fullFileName.lastIndexOf('/')));
  qDebug() << l_destinationDir.absolutePath();
  if (!l_destinationDir.exists())
    l_destinationDir.mkdir(l_destinationDir.absolutePath());

  // Save file
  QFile l_saveFile(l_fullFileName);
  l_saveFile.open(QIODevice::WriteOnly);
  l_saveFile.write(p_data);
  l_saveFile.close();
  NOT_IMPLEMENTED;
}

QString Share::ResourceStorageUnitLocalCache::computeFileName(QByteArray p_data)
{
  WHERE;
  QCA::init();
  if (!QCA::isSupported("sha1"))
    qDebug() << "SHA1 not supported";
  QCA::Hash l_hash("sha1");
  NOT_IMPLEMENTED;
  QString l_hashStr = l_hash.hashToString(p_data);
  qDebug() << "Hash : " << l_hashStr;
  return l_hashStr.left(2) + QString("/") + l_hashStr;
}
