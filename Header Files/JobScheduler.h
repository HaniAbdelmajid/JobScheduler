#ifndef JOBSCHEDULER_H
#define JOBSCHEDULER_H

#include "Job.h"
#include <QObject>
#include <QThread>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

// This class is responsible for managing and running scheduled jobs in a separate thread.
class JobScheduler : public QThread {

    Q_OBJECT  // Enables Qt's signal-slot mechanism

private:
    QQueue<Job> jobQueue;  // Stores jobs in a queue, waiting for execution
    QMutex mutex;  // Prevents multiple threads from modifying the job queue at the same time
    QWaitCondition condition;  // Used to pause execution when no jobs are available

    bool stopFlag = false;  // Flag to indicate when the scheduler should stop

public:
    explicit JobScheduler(QObject *parent = nullptr);  // Constructor
    ~JobScheduler();  // Destructor to properly stop the scheduler

    void scheduleJob(const Job& job);  // Adds a job to the queue
    void run() override;  // Main loop that picks and executes jobs

signals:
    // Emitted whenever a job is executed so the UI can update
    void jobExecuted(QString jobName, QString priorityLabel, QString timestamp);
};

#endif // JOBSCHEDULER_H
