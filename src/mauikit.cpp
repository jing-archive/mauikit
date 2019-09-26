/*
 *   Copyright 2018 Camilo Higuita <milo.h@aol.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "mauikit.h"

#include <QDebug>

#include "fm.h"
#include "fmh.h"

#include "mauimodel.h"
#include "mauilist.h"
#include "placeslist.h"
#include "fmlist.h"
#include "pathlist.h"

#include "tagsmodel.h"
#include "tagslist.h"

#include "storemodel.h"
#include "storelist.h"

#include "handy.h"
#include "documenthandler.h"
#include "syntaxhighlighterutil.h"

#include "mauiaccounts.h"
#include "mauiapp.h"

#ifdef Q_OS_ANDROID
#include "mauiandroid.h"
#else
#include "mauikde.h"
#endif

#if defined Q_OS_ANDROID || defined APPIMAGE_PACKAGE
#include <QIcon>
#include <QQuickStyle>
#endif

#ifdef STATIC_MAUIKIT
#include "kquicksyntaxhighlighter/kquicksyntaxhighlighter.h"
#endif

QUrl MauiKit::componentUrl(const QString &fileName) const
{
#ifdef MAUI_APP
    return QUrl(QStringLiteral("qrc:/maui/kit/") + fileName);
#else
    return QUrl(resolveFileUrl(fileName));
#endif
}

void MauiKit::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("org.kde.mauikit"));

    qmlRegisterSingletonType(componentUrl(QStringLiteral("Style.qml")), uri, 1, 0, "Style");
    qmlRegisterType(componentUrl(QStringLiteral("ToolBar.qml")), uri, 1, 0, "ToolBar");
    qmlRegisterType(componentUrl(QStringLiteral("ApplicationWindow.qml")), uri, 1, 0, "ApplicationWindow");
    qmlRegisterType(componentUrl(QStringLiteral("Page.qml")), uri, 1, 0, "Page");
    qmlRegisterType(componentUrl(QStringLiteral("ShareDialog.qml")), uri, 1, 0, "ShareDialog");
    qmlRegisterType(componentUrl(QStringLiteral("PieButton.qml")), uri, 1, 0, "PieButton");
    qmlRegisterType(componentUrl(QStringLiteral("SideBar.qml")), uri, 1, 0, "SideBar");
    qmlRegisterType(componentUrl(QStringLiteral("Holder.qml")), uri, 1, 0, "Holder");
    qmlRegisterType(componentUrl(QStringLiteral("GlobalDrawer.qml")), uri, 1, 0, "GlobalDrawer");
    qmlRegisterType(componentUrl(QStringLiteral("ListDelegate.qml")), uri, 1, 0, "ListDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("ListBrowserDelegate.qml")), uri, 1, 0, "ListBrowserDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("ListItemDelegate.qml")), uri, 1, 0, "ListItemDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("GridItemDelegate.qml")), uri, 1, 0, "GridItemDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("GridBrowserDelegate.qml")), uri, 1, 0, "GridBrowserDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("SelectionBar.qml")), uri, 1, 0, "SelectionBar");
    qmlRegisterType(componentUrl(QStringLiteral("LabelDelegate.qml")), uri, 1, 0, "LabelDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("NewDialog.qml")), uri, 1, 0, "NewDialog");
    qmlRegisterType(componentUrl(QStringLiteral("Dialog.qml")), uri, 1, 0, "Dialog");
    qmlRegisterType(componentUrl(QStringLiteral("AboutDialog.qml")), uri, 1, 0, "AboutDialog");
    qmlRegisterType(componentUrl(QStringLiteral("Popup.qml")), uri, 1, 0, "Popup");
    qmlRegisterType(componentUrl(QStringLiteral("TextField.qml")), uri, 1, 0, "TextField");
    qmlRegisterType(componentUrl(QStringLiteral("Badge.qml")), uri, 1, 0, "Badge");
    qmlRegisterType(componentUrl(QStringLiteral("GridView.qml")), uri, 1, 0, "GridView");
    qmlRegisterType(componentUrl(QStringLiteral("ColorsBar.qml")), uri, 1, 0, "ColorsBar");
    qmlRegisterType(componentUrl(QStringLiteral("ImageViewer.qml")), uri, 1, 0, "ImageViewer");

    /** STORE CONTROLS, MODELS AND INTERFACES **/
    qmlRegisterType<StoreList>("StoreList", 1, 0, "StoreList");
    qmlRegisterType<StoreModel>("StoreModel", 1, 0, "StoreModel");
    qmlRegisterType(componentUrl(QStringLiteral("private/StoreDelegate.qml")), uri, 1, 0, "StoreDelegate");
    qmlRegisterType(componentUrl(QStringLiteral("Store.qml")), uri, 1, 0, "Store");

    /** BROWSING CONTROLS **/
    qmlRegisterType(componentUrl(QStringLiteral("ListBrowser.qml")), uri, 1, 0, "ListBrowser");
    qmlRegisterType(componentUrl(QStringLiteral("GridBrowser.qml")), uri, 1, 0, "GridBrowser");

    /** FM CONTROLS, MODELS AND INTERFACES **/
    qmlRegisterType<PlacesList>(uri, 1, 0, "PlacesList");
    qmlRegisterType<FMList>(uri, 1, 0, "FMList");
    qmlRegisterType<PathList>(uri, 1, 0, "PathList");
    qmlRegisterSingletonType<FM>(uri, 1, 0, "FM",
                                 [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return new FM;
    });
    //     qmlRegisterSingletonType(componentUrl(QStringLiteral("private/FileBrowser.qml")), uri, 1, 0, "FileMenu");
    qmlRegisterType(componentUrl(QStringLiteral("FileBrowser.qml")), uri, 1, 0, "FileBrowser");
    qmlRegisterType(componentUrl(QStringLiteral("PlacesSidebar.qml")), uri, 1, 0, "PlacesSidebar");
    qmlRegisterType(componentUrl(QStringLiteral("FilePreviewer.qml")), uri, 1, 0, "FilePreviewer");
    qmlRegisterType(componentUrl(QStringLiteral("FileDialog.qml")), uri, 1, 0, "FileDialog");
    qmlRegisterType(componentUrl(QStringLiteral("PathBar.qml")), uri, 1, 0, "PathBar");
    qmlRegisterType(componentUrl(QStringLiteral("SyncDialog.qml")), uri, 1, 0, "SyncDialog"); //to be rename to accountsDialog

    /** EDITOR CONTROLS **/
    qmlRegisterType<DocumentHandler>(uri, 1, 0, "DocumentHandler");
    qmlRegisterType<SyntaxHighlighterUtil>();
    qmlRegisterType(componentUrl(QStringLiteral("Editor.qml")), uri, 1, 0, "Editor");
#ifdef STATIC_MAUIKIT
    qmlRegisterType<KQuickSyntaxHighlighter>("org.kde.kquicksyntaxhighlighter", 0, 1, "KQuickSyntaxHighlighter");
#endif

    /** PLATFORMS SPECIFIC CONTROLS **/
#ifdef Q_OS_ANDROID
    qmlRegisterSingletonType<MAUIAndroid>(uri, 1, 0, "Android",
                                          [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return new MAUIAndroid;
    });
#else
    qmlRegisterType(componentUrl(QStringLiteral("Terminal.qml")), uri, 1, 0, "Terminal");
    qmlRegisterSingletonType<MAUIKDE>(uri, 1, 0, "KDE",
                                      [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return new MAUIKDE;
    });
#endif

    /** DATA MODELING TEMPLATED INTERFACES **/
    qmlRegisterType<MauiList>(); //ABSTRACT BASE LIST
    qmlRegisterType<MauiModel>(uri, 1, 0, "BaseModel"); //BASE MODEL

    /** TAGGING INTERFACES AND MODELS **/
    qmlRegisterType<TagsList>("TagsList", 1, 0, "TagsList");
    qmlRegisterType<TagsModel>("TagsModel", 1, 0, "TagsModel");
    qmlRegisterType(componentUrl(QStringLiteral("private/TagList.qml")), uri, 1, 0, "TagList");
    qmlRegisterType(componentUrl(QStringLiteral("TagsBar.qml")), uri, 1, 0, "TagsBar");
    qmlRegisterType(componentUrl(QStringLiteral("TagsDialog.qml")), uri, 1, 0, "TagsDialog");

    /** MAUI APPLICATION SPECIFIC PROPS **/
    qmlRegisterType<MauiAccounts>();
    qmlRegisterUncreatableType<MauiApp>(uri, 1, 0, "App", "Cannot be created App");

    /** HELPERS **/
    qmlRegisterSingletonType<Handy>(uri, 1, 0, "Handy",
                                    [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject* {
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        return new Handy;
    });

#if defined Q_OS_ANDROID || defined APPIMAGE_PACKAGE
    QIcon::setThemeSearchPaths({":/icons/luv-icon-theme"});
    QIcon::setThemeName("Luv");
    QQuickStyle::setStyle(":/style");
#endif

    qmlProtectModule(uri, 1);
}
