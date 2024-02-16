#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <pwd.h>
#include <unistd.h>
#include "browse.h"
#include "filenames.h"
using namespace qfilelib;
//TODO: Add BMP, GIF, PNM and TIFF filetypes
void MainWindow::on_browseButton_clicked()
{
    QStringList fileNames = browseMultiple(this,"Select image","PNG files (*.png)");
    if(fileNames.isEmpty()) return;
    escapeFilenames(fileNames);
    QString text = fileNames.join(" ");
    ui->inputLine->setText(text);
}
void MainWindow::on_outputBrowseButton_clicked()
{
    QString folderName = browseFolder(this,"Select folder");
    if(folderName == "") return;
    ui->outputLine->setText(folderName);
}
