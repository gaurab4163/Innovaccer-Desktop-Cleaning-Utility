# Innovacer-Desktop-Cleaning-Utility
1. Cleans and helps organize the desktop by moving files to separate folder based on extension
2. Finds the top 10 largest files in the system.


# How to install/Run
It's pretty straight forward like running any other c++ program
1. Open terminal
2. cd to the directory containing the file "organizeDesktop.cpp"
3. Type "g++ organizeDesktop.cpp" without quotes
4. Type "./a.out" without quotes

Video of Program Demonstration:  
https://www.youtube.com/watch?v=jNE4rfdPNvM

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
