Job Scheduler GUI

Job Scheduler GUI is a C++ & Qt-based application that allows users to schedule, manage, and execute jobs with priority-based execution and delays. 
The project utilizes multi-threading to handle jobs efficiently and features a graphical user interface (GUI) built with Qt.

# Features

  - GUI Interface: Easily schedule jobs using a user-friendly Qt-based interface.
  - Priority-Based Execution: Jobs are scheduled as High, Medium, or Low demand.
  - Job Delays: Set a delay time before a job executes.
  - Multi-Threaded Processing: Jobs run efficiently in a separate thread.
  - Real-Time Job Logs: View executed jobs with timestamps in the UI.
    

## Installation & Setup

1. Clone the Repository

git clone https://github.com/YOUR_USERNAME/JobSchedulerGUI.git
cd JobSchedulerGUI

2. Install Dependencies

Ensure you have Qt 6+ installed. Qt comes with CMake, so you usually don’t need to download it separately. However, if CMake is missing, you can download it here:

Download Qt: https://www.qt.io/download

Download CMake (if needed): https://cmake.org/download/

Note: The GUI file and CMake files should not be placed inside a folder within Qt ( I placed them in a folder just for organization but once qt is downloaded take them out ). 
They must remain in the main project directory for proper recognition.

3. Build the Project
  - Once Qt is fully and correctly installed, create a Qt Widgets Application Project. Move all the files to the said folder, making sure to remove the new beginner header and cpp files generated.
  - Then add my respective code to the QT folder the way I stated then press the big pause green looking button, then the code should build and run accordingly!


### How to Use

 - Enter a Job Name in the text field.

 - Select Job Priority (High, Medium, or Low Demand) from the dropdown.

 - Set Delay Time using the spin box.

 - Click "Add Job" to schedule it.

 - View the executed jobs in the log table.
