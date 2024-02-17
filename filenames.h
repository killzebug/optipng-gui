#ifndef QFIRE_FILENAMES_H
#define QFIRE_FILENAMES_H
#include <QString>
#include <QStringList>
namespace qfilelib {
inline void escapeFilename(QString& fileName)
{
    if(fileName.isEmpty()) return;
    for(int i = fileName.size() - 1; i >= 0; i--)
    {
        auto ch = fileName[i];
        if(ch == ' ' || ch == '\\' || ch == '\"' || ch == ';' || ch == '(' || ch == ')' || ch == '&' || ch == '{' || ch == '}')
        {
            fileName.insert(i,'\\');
        }
    }
}
inline void escapeFilenames(QStringList& fileNames)
{
    for(auto& name : fileNames)
    {
        escapeFilename(name);
    }
}
inline bool isEscaped(const QString& line, int i)
{
    if(i == 0) return false;
    bool escaped{false};
    for(i -= 1;i >= 0; i--)
    {
        if(line[i] == '\\') escaped = !escaped;
        else return escaped;
    }
    return escaped;
}

inline QStringList separateFilenames(const QString& text)
{
    if(text.isEmpty()) return QStringList();
    QStringList out;
    int lastChar{text.size() - 1};
    int wordBeginning{0};
    for(int i = 0; i <= lastChar; i++)
    {
        i = text.indexOf(' ', i);
        if(i == -1) i = lastChar;
        if(i == lastChar || isEscaped(text,i) == false)
        {
            //increment i because the last character of the word is at i + 1 (counting from 0)
            ++i;

            int wordSize = i - wordBeginning;

            //make a new substring, add to list
            out.append(text.mid(wordBeginning,wordSize));

            wordBeginning = i;
        }
    }
    return out;
}

}//ns

#endif // QFIRE_FILENAMES_H
