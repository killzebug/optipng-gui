#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QErrorMessage>

#include "optimizationqueue.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateQueueStatus(uint* status);
    void buildCommand(std::string,std::string);
private slots:
    void on_browseButton_clicked();

    void on_optimizeButton_clicked();

    void on_outputBrowseButton_clicked();

private:
    Ui::MainWindow *ui;
    QErrorMessage noOutputFolder;
    QErrorMessage noImage;
    OptimizationQueue optimization;
};
#endif // MAINWINDOW_H
