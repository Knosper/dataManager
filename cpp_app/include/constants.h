// Constants.h
#pragma once

#include <string>

namespace AppConfig {
    //Application Information not used yet
    const std::string APP_NAME = "Data Manager";
    const std::string APP_VERSION = "1.0.0";
    const std::string APP_AUTHOR = "JJ";
    const std::string APP_EMAIL = "";

    //Paths to the images
    #define _THUB_PATH "misc/Thub.jpg"
    #define _ICON_APPERANCE "misc/menu_icons/Icon_Apperance.png"
    #define _ICON_DATABASE_BACKUP "misc/menu_icons/Icon_Backup.png"
    #define _ICON_BUG "misc/menu_icons/Icon_Bug.jpg"
    #define _ICON_CREATE_DATABASE "misc/menu_icons/Icon_Create_Database.png"
    #define _ICON_DATABASE_LOGS "misc/menu_icons/Icon_Database_Logs.png"
    #define _ICON_DATABASE "misc/menu_icons/Icon_Database.png"
    #define _ICON_DELETE_DATABASE "misc/menu_icons/Icon_Delete_Database.png"
    #define _ICON_DOCS "misc/menu_icons/Icon_Docs.png"
    #define _ICON_DATABASE_IMPORT "misc/menu_icons/Icon_Import.png"
    #define _ICON_DATABASE_EXPORT "misc/menu_icons/Icon_Export.png"
    #define _ICON_HELP "misc/menu_icons/Icon_Help.png"
    #define _ICON_LIST_DATABASE "misc/menu_icons/Icon_List_Database.jpg"
    #define _ICON_MANAGE_CONNECTION "misc/menu_icons/Icon_Manage_Connection.png"
    #define _ICON_NEW_CONNECTION "misc/menu_icons/Icon_New_Connection.png"
    #define _ICON_PREFERENCES "misc/menu_icons/Icon_Preferences.png"
    #define _ICON_RESTORE "misc/menu_icons/Icon_Restore.png"
    #define _ICON_SETTINGS "misc/menu_icons/Icon_Settings.png"
    #define _ICON_TOOLS "misc/menu_icons/Icon_Tools.png"
    #define _ICON_UPDATE "misc/menu_icons/Icon_Update.png"
    #define _ICON_VISUALIZE_DATABASE "misc/menu_icons/Icon_Visualize_Database.png"

    //MenuBar Items
    enum class SelectedMenuItem 
    {
        StartPage,
        ListDatabases,
        NewConnection,
        ManageConnections,
        ImportConnection,
        ExportConnection,
        CreateDatabase,
        DeleteDatabase,
        BackupDatabase,
        RestoreDatabase,
        VisualizeDatabase,
        DatabaseLogs,
        Preferences,
        Appearance,
        Docs,
        CheckForUpdates
    };
};