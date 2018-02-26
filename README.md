# Innovacer-Desktop-Cleaning-Utility
1. Cleans and helps organize the desktop by moving files to separate folder based on extension
2. Finds the top 10 largest files in the system.


# How to install/Run
It's pretty straight forward like running any other c++ program
1. Open terminal
2. cd to the directory containing the file "organizeDesktop.cpp"
3. Type "g++ organizeDesktop.cpp" without quotes
4. Type "./a.out" without quotes

# Corner cases this program can handle(minor features)
(Desktop CleanUp)
1. If file with same name already exists in destination(Documents folder), the file in the Desktop would be renamed by     appending number in the end before moving.
2. Is completely automatic and doesn't require any user input i.e. User doesn't need to enter full path of Desktop or Documents folder in terminal
3. Doesn't touch application shortucts(.desktop extension) and symbolic links(folder shortcuts)
4. Moves folders present in the Desktop to "otherFolders" folder in the destination
5. Handles extensionless files(e.g. executable files) by moving them in "extensionLess" folder

(10 largest files)

6. Avoids scanning symbolic links(folder shortcuts) to avoid scanning the same files(contained in shortcut folder) multiple times
7. Use of Heap to efficiently store and update 10 largest files.

# Limitations
1. Works only on Linux as of now. Couldn't make it cross-platform due to exams and other academic engagements and thus, limitation of time.
2. While finding largest files, scans the home directory and media directory. If "/" is given as the source path, segmentation fault occurs. Although unlikey that these system folders might contain largest file, there is a possibility. Couldn't think of efficient solution around this problem as of now.

# Plans to do in near future(Features to add)
1. Make it cross platform to work well in both windows and linux, without any user input(automatically detect if windows or linux and run respective portions of code)
2. Add GUI. I had been experimenting a lot lately with Qt, but couldn't write GUI because of time limitation and my other academic engagements(exams). It would greatly help novice users who are unacquainted with terminal

# Youtube video on how to run this program
https://www.youtube.com/watch?v=VpsBJHMZmSg

# System/environment on which this program ran
Ubuntu 16.04, Tested in Code::Blocks IDE





