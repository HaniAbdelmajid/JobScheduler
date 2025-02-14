#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "JobScheduler.h"

// Constructor: Sets up the UI and starts the job scheduler
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    scheduler = new JobScheduler(this);  // Initialize the scheduler

    // Connect the scheduler signal to update the UI when a job is executed
    connect(scheduler, &JobScheduler::jobExecuted, this, &MainWindow::updateJobTable);
    scheduler->start();  // Start job processing
}

// Destructor: Cleans up memory when the window is closed
MainWindow::~MainWindow() {
    delete ui;
    delete scheduler;  // Prevents memory leaks
}

// Handles what happens when the "Add Job" button is clicked
void MainWindow::on_addJobButton_clicked() {
    QString name = ui->jobNameEdit->text();
    if (name.isEmpty()) {
        ui->statusbar->showMessage("Please enter a job name!", 2000);
        return;
    }

    // Get the selected priority from the combo box (dropdown menu)
    int priorityIndex = ui->priorityComboBox->currentIndex();  // 0 = High, 1 = Medium, 2 = Low
    int priority;

    // Convert selected priority index to actual priority values
    if (priorityIndex == 0) priority = 8;  // High Demand
    else if (priorityIndex == 1) priority = 5;  // Medium Demand
    else priority = 2;  // Low Demand

    // Get the delay time (in seconds) from the spin box
    int delay = ui->delaySpinBox->value();

    // Debugging output to confirm the selected values
    qDebug() << "Selected Index: " << priorityIndex;
    qDebug() << "Selected Text: " << ui->priorityComboBox->currentText();
    qDebug() << "Assigned Priority: " << priority;
    qDebug() << "Job Delay: " << delay << "seconds";

    // Schedule the job with the chosen delay and priority
    auto now = std::chrono::system_clock::now();
    Job newJob(name.toStdString(), []() {}, now + std::chrono::seconds(delay), priority);
    scheduler->scheduleJob(newJob);

    ui->jobNameEdit->clear();  // Reset the input field after adding the job
}

// Updates the job table in the UI when a job is executed
void MainWindow::updateJobTable(QString jobName, QString priority, QString timestamp) {
    int row = ui->jobTable->rowCount();
    ui->jobTable->insertRow(row);

    // Add a new row to the table with job execution details
    ui->jobTable->setItem(row, 0, new QTableWidgetItem(timestamp));
    ui->jobTable->setItem(row, 1, new QTableWidgetItem(jobName));
    ui->jobTable->setItem(row, 2, new QTableWidgetItem(priority));
}
