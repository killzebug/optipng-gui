#ifndef QFIRE_BROWSE_H
#define QFIRE_BROWSE_H
#include <QFileDialog>
#include <pwd.h>
#include <unistd.h>
#include <filesystem>
namespace qfilelib {
inline std::wstring getPathFolder(const std::wstring& path)
{
    std::wstring folder;
    auto folderPos = path.find_last_of('/');
    folder = path.substr(0,folderPos);
    return folder;
}
inline const char* getHomeDirectory()
{
    return getpwuid(getuid())->pw_dir;
}
inline QString lastFolder;
//Checks if the last visited folder exists, sets it to the home directory if it does not
inline void _checkLastFolder()
{
    if(lastFolder == nullptr || std::filesystem::exists(lastFolder.toStdWString()) == false)
    {
        lastFolder = getHomeDirectory();
    }
}
inline void _setLastFolder(QString& fileName)
{
    if(fileName != "") //Cancel returns empty string
    {
        lastFolder = QString::fromStdWString( getPathFolder(fileName.toStdWString()) );
    }
}
inline QString browse(QWidget* parent,const QString& caption,const QString& filter)
{
    _checkLastFolder();

    QString fileName = QFileDialog::getOpenFileName(parent,caption,lastFolder,filter);

    _setLastFolder(fileName);

    return fileName;
}
inline QStringList browseMultiple(QWidget* parent, const QString& caption, const QString& filter)
{
    _checkLastFolder();

    QStringList fileNames = QFileDialog::getOpenFileNames(parent,caption,lastFolder,filter);
    if(!fileNames.isEmpty())
    _setLastFolder(fileNames[0]);

    return fileNames;
}
inline QString browseFolder(QWidget* parent,const QString& caption)
{
    _checkLastFolder();

    QString folderName = QFileDialog::getExistingDirectory(parent,caption,lastFolder);

    if(folderName != "") lastFolder = folderName;

    return folderName;
}
} // ns
#endif // QFIRE_BROWSE_H
