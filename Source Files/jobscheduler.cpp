#include "JobScheduler.h"
#include <QDateTime>
#include <QDebug>

// Constructor: Initializes the job scheduler thread
JobScheduler::JobScheduler(QObject *parent) : QThread(parent) {}

// Destructor: Stops the scheduler gracefully
JobScheduler::~JobScheduler() {
    stopFlag = true;  // Tell the thread to stop
    condition.wakeAll();  // Wake up any waiting threads so they can exit

    wait();  // Ensure the thread fully shuts down
}

// Adds a new job to the queue and notifies the worker thread
void JobScheduler::scheduleJob(const Job& job) {
    QMutexLocker locker(&mutex);  // Lock the queue to prevent race conditions

    jobQueue.enqueue(job);  // Add job to the queue

    condition.wakeOne();  // Wake up the worker thread to process the job
}

// Main worker thread that continuously checks and executes jobs
void JobScheduler::run() {
    while (!stopFlag) {
        Job job("", []() {}, std::chrono::system_clock::now(), -1);  // Default placeholder job

        {
            QMutexLocker locker(&mutex);  // Lock access to the queue
            while (jobQueue.isEmpty() && !stopFlag) {
                condition.wait(&mutex);  // Wait for new jobs unless stopping
            }

            if (stopFlag) return;  // If stop flag is set, exit the loop

            job = jobQueue.dequeue();  // Get the next job from the queue
        }

        QThread::sleep(2);  // Simulate job execution delay (this can be adjusted)

        // Get the current timestamp for logging
        QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");

        // Emit signal to notify the UI that a job was executed
        emit jobExecuted(QString::fromStdString(job.name),
                         QString::fromStdString(job.getPriorityLabel()),
                         timestamp);
    }
}
