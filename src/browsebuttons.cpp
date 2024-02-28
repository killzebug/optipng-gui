#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <pwd.h>
#include <unistd.h>
#include "../libs/browse.h"
#include "../libs/filenames.h"
using namespace qfilelib;
void MainWindow::on_browseButton_clicked()
{
    QStringList fileNames = browseMultiple(this,"Select image",
        //Image format filters, non-png formats are converted to png.
        "PNG images (*.png);;"
        "Convertable image formats (*.png *.bmp  *.pnm *.tiff);;"
        //"GIF files (*.gif);;" //would convert a gif file to a png needs -snip enabled needs testing
        "BMP images (*.bmp);;"
        "PNM images (*.pnm);;"
        "TIFF images (*.tiff)");
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
