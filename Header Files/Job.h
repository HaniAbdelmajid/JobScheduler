#ifndef JOB_H
#define JOB_H

#include <iostream>
#include <functional>
#include <chrono>
#include <iomanip>
#include <string>

// Represents a job that will be scheduled and executed
class Job {
public:
    std::string name;  // The name of the job (for logging and display)
    std::function<void()> task;  // The actual function/task to run when the job executes
    std::chrono::time_point<std::chrono::system_clock> executeAt;  // Time when the job should run

    int priority;  // Priority level (higher means more important)
    int repeatCount;  // How many times this job should repeat (0 = one-time job)

    std::chrono::seconds interval;  // Time between repeats (if it's a recurring job)

    // Constructor to set up a new job with all required details
    Job(std::string jobName, std::function<void()> t,
        std::chrono::time_point<std::chrono::system_clock> time,
        int p, int r = 0, std::chrono::seconds i = std::chrono::seconds(0))
        : name(jobName), task(t), executeAt(time), priority(p), repeatCount(r), interval(i) {}

    // Used to compare jobs in a priority queue (higher priority jobs are executed first)
    bool operator<(const Job& other) const {
        return priority < other.priority;
    }

    // Converts the priority integer into a human-friendly label
    std::string getPriorityLabel() const {
        if (priority >= 7) return "High Demand";  // Most urgent jobs

        if (priority >= 4) return "Medium Demand";  // Important but not urgent

        return "Low Demand";  // Least priority jobs
    }
};

#endif // JOB_H
