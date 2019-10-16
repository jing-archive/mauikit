#ifndef FMSTATIC_H
#define FMSTATIC_H

#include <QObject>
#include "fmh.h"

class FMStatic : public QObject
{
    Q_OBJECT
public:
    explicit FMStatic(QObject *parent = nullptr);

public slots:
    static FMH::MODEL_LIST search(const QString &query, const QUrl &path, const bool &hidden = false, const bool &onlyDirs = false, const QStringList &filters = QStringList());

    static FMH::MODEL_LIST getDevices();
    static FMH::MODEL_LIST getDefaultPaths();

    static FMH::MODEL_LIST packItems(const QStringList &items, const QString &type);

	static bool copy(QUrl sourceDir, QUrl destinationDir, bool overWriteDirectory = false);
	static bool cut(QUrl url, QUrl where);
	static bool removeDir(const QUrl &path);

	static QString formatSize(const int &size);
	static QString formatTime(const qint64 &value);
	static QString formatDate(const QString &dateStr, const QString &format = QString("dd/MM/yyyy"), const QString &initFormat = QString());
    static QString homePath();
    static QUrl parentDir(const QUrl &path);

    static QVariantMap getDirInfo(const QUrl &path, const QString &type);
    static QVariantMap getFileInfo(const QUrl &path);

    static bool isDefaultPath(const QString &path);
    static bool isDir(const QUrl &path);
    static bool isApp(const QString &path);
    static bool isCloud(const QUrl &path);
    static bool fileExists(const QUrl &path);

    /**
     * if the url is a file path then it returns its directory
     * and if it is a directory returns the same path
     * */
    static QString fileDir(const QUrl &path);

    /* SETTINGS */
    static void saveSettings(const QString &key, const QVariant &value, const QString &group);
    static QVariant loadSettings(const QString &key, const QString &group, const QVariant &defaultValue);

    static QVariantMap dirConf(const QUrl &path);
    static void setDirConf(const QUrl &path, const QString &group, const QString &key, const QVariant &value);

    static bool removeFile(const QUrl &path);
    static void moveToTrash(const QUrl &path);
    static void emptyTrash();
    static bool rename(const QUrl &path, const QString &name);
    static bool createDir(const QUrl &path, const QString &name);
    static bool createFile(const QUrl &path, const QString &name);
    static bool createSymlink(const QUrl &path, const QUrl &where);

    static bool openUrl(const QUrl &url);
    static void openLocation(const QStringList &urls);
};

#endif // FMSTATIC_H
