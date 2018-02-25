# Innovacer-Desktop-Cleaning-Utility
1. Cleans and helps organize the desktop by moving files to separate folder based on extension
2. Finds the top 10 largest files in the system.

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
2. While finding largest files, scans the home directory and media directory. If "/" is given as the source path, segmentation fault is reached. Although unlikey that these system folders might contain largest file, there is a possibility. Couldn't think around this problem as of now.

# Plan to do 



