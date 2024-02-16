#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <string>
#include <filesystem>
#include <QThread>
#include "filenames.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());

    connect(&optimization,&OptimizationQueue::updateStatus,this,&MainWindow::updateQueueStatus);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::buildCommand(std::string fileName,std::string flags)
{
    std::string command{"optipng "};
    command += flags;
    command += ' ';

    if(ui->newfileButton->isChecked())
    {
        auto outputFolder = ui->outputLine->text().toStdString();
        if(std::filesystem::exists(outputFolder) == false)
        {
            noOutputFolder.showMessage("No output folder provided.");
            return;
        }

        std::string outputPath{"-clobber -dir \""};

        outputPath += outputFolder;
        outputPath += "\" ";
        command += outputPath;
    }
    command += fileName;

    optimization.queue(command.c_str());
}
void MainWindow::on_optimizeButton_clicked()
{
    auto fileNames = ui->inputLine->text();
    if(fileNames == "")
    {
        noImage.showMessage("Please provide an image.");
        return;
    }
    std::string flags{ui->comboBox->currentText().toStdString()};

    auto fileNameList = qfilelib::separateFilenames(fileNames);
    for(auto& fileName : fileNameList)
    {
        //todo: show a no image provided error. Need to do that through shell because stl filesystem stuff doesn't accept shell sanitized filenames
        //noImage.showMessage("No image provided. Escape spaces and characters ; \ \" with a backslash if you entered the filename manually");
        buildCommand(fileName.toStdString(),flags);
    }

}
void MainWindow::updateQueueStatus(uint* status)
{
    QString statusText = QString("%1/%2 complete.").arg(QString::number(status[0]),QString::number(status[1]));
    uint& errorCount = status[2];
    if(errorCount != 0)
    {
        QChar plurality{};
        if(status[2] > 1) plurality = 's';
        statusText += QString(" (%1 error%2)").arg(QString::number(errorCount),plurality);
    }
    ui->statusBar->showMessage(statusText);
    //delete[] status;
}
