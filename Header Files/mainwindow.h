#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "JobScheduler.h"  // Manages job scheduling in the background

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Main application window for the job scheduler UI
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);  // Constructor
    ~MainWindow();  // Destructor

private slots:
    void on_addJobButton_clicked();  // Handles adding a new job when the button is clicked
    void updateJobTable(QString jobName, QString priority, QString timestamp);  // Updates the UI table with job details

private:
    Ui::MainWindow *ui;  // Pointer to the UI components
    JobScheduler *scheduler;  // Handles job execution in a separate thread
};

#endif // MAINWINDOW_H
