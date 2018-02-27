#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>//for pwd.h to work. unistd doesn't work in windows
#include <pwd.h>
#include <cstdlib>
#include <string>
#include <sstream>


using namespace std;








/**
    Following code segment works to clean up the Desktop
 */








typedef vector<string> stringvec;

bool checkExtensionSeen(stringvec seenExtensions,string extensionToCheck){
    for(stringvec::iterator itr=seenExtensions.begin();itr!=seenExtensions.end();itr++){
        if(*itr==extensionToCheck)
            return true;
    }
    return false;

}


void organizeDesktop(const string& homePath, stringvec& seenExtensions)
{

    string sourceFile= __FILE__;
/**
  done to skip moving current file "cleanUp.cpp", under execution... Else, get message, "file no longer exists"
  Compiling in Terminal, sourceFile=cleanUp.cpp
  Comiping and Running in IDE like Code::Blocks, sourceFile= /home/gaurab/Desktop/cleanUp.cpp
  */

    /*Hence to maintain sourceFile name uniformity and extract only fileName, following code exists*/
    int pos_found=sourceFile.rfind("/");    //Guaranteed to work since "/" aren't allowed in normal file names
    if(pos_found==string::npos)
        pos_found=-1;
    sourceFile=sourceFile.substr(pos_found+1);  //better to overwrite than create new var
    /*maintaining uniformity code finished*/

    string curDirFullPath=homePath+"/Desktop";
    DIR* dirp = opendir(curDirFullPath.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        string extension;   //it contains the extension of current file
        string fileName=dp->d_name;
        if(fileName==sourceFile)    //skip moving this current file "cleanUp.cpp" under execution
        	continue;

        //check if folder or file and if file, find extension
        string path=curDirFullPath+"/"+fileName;
        struct stat s;

        if( lstat(path.c_str(),&s) == 0 )
        {

            if( S_ISLNK(s.st_mode) ){    //is a symbolic link; similar to shortcut for folders
                cout<<"Skipped moving Shortcut: "<<fileName<<endl<<endl;
                continue;
            }

            else if( S_ISDIR(s.st_mode) )   //it's a directory
                extension="otherFolders";

            else if( S_ISREG(s.st_mode) )  //it's a file
            {
                size_t found=fileName.rfind(".");
                if(found!=string::npos)    //extension exists
                    extension=fileName.substr(found+1);
                else
                    extension="extensionLess";  //this will be name of folder for extension less files

                if(extension=="desktop")    //skip application shortcuts in linux e.g: chrome
                    continue;
            }
        }
        else    //error
            cout<<"error in using stat"<<endl;

        string newDirFullPath=homePath+"/Documents/"+extension;

        if(!checkExtensionSeen(seenExtensions,extension)){  //directory doesn't exist for current extension
            seenExtensions.push_back(extension);
            int status=mkdir(newDirFullPath.c_str(),0777);
            if(status!=0)
                cout<<"Directory already exists for extension "<<extension<<endl<<endl;
            else
                cout<<"Created directory '"<<extension<<"'"<<endl<<endl;

        }
        string oldFilePath=curDirFullPath+"/"+fileName;
        string newFilePath=newDirFullPath+"/"+fileName;

        //check if another file exists at destination with same file name
        struct stat buffer;
        string tempPath=newFilePath;
        int i=1;    //number added if two files with same file name exists
        while(1){
                if( lstat(tempPath.c_str(),&buffer) == 0 ){
                stringstream ss;
                ss << i;
                //std::string str = ss.str();
                tempPath=newFilePath+ss.str();
                i++;
            }
            else{
                newFilePath=tempPath;break;
            }
        }


        int renameStatus=rename(oldFilePath.c_str(),newFilePath.c_str());
        if(renameStatus!=0)
            cout<<"Didn't copy to correct directory for file: "<<fileName<<endl<<endl;
        else
            cout<<"Moved file "<<fileName<<endl<<endl;
    }
    closedir(dirp);
}









/**
   Code to clean the desktop finishes.
   Code to find the top 10 files in the system starts
 */











// User defined class FileProperties
struct fileProperties{
   string fileName;
   double fileSize;
};

int totalFilesScanned=0; //count total number of files Scanned

class MinHeap{
public:
    fileProperties *harr;
    int capacity;
    int heap_size;

    MinHeap(int capacity);

    void MinHeapify(int );

    int parent(int i) { return (i-1)/2; }

    int left(int i) { return (2*i + 1); }

    int right(int i) { return (2*i + 2); }

    fileProperties extractMin();

    fileProperties getMin() { return harr[0]; }

    double getMinFileSize() { return harr[0].fileSize; }

    void insertKey(fileProperties k);
    void swap(fileProperties *x, fileProperties *y);
};

MinHeap::MinHeap(int cap){ //constructor to build heap of given size
    heap_size = 0;
    capacity = cap;
    harr = new fileProperties[cap];
}

void MinHeap::insertKey(fileProperties k)
{
    if (heap_size == capacity){
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
    //to heapify if elements in heap disarranged
    while (i != 0 && harr[parent(i)].fileSize > harr[i].fileSize){
       swap(&harr[i], &harr[parent(i)]);
       i = parent(i);
    }
}

//remove min element from heap
fileProperties MinHeap::extractMin(){
    if (heap_size == 1){
        heap_size--;
        return harr[0];
    }
    //store min value of heap to return later
    fileProperties root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
    return root;
}

void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].fileSize < harr[i].fileSize)
        smallest = l;
    if (r < heap_size && harr[r].fileSize < harr[smallest].fileSize)
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

void MinHeap::swap(fileProperties *x, fileProperties *y)
{
    fileProperties temp = *x;
    *x = *y;
    *y = temp;
}

//recursive function to scan each directory and find largest file
void findLargestFiles( MinHeap &h, string mediaPath){
    string curDirFullPath=mediaPath;
    DIR* dirp = opendir(curDirFullPath.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        totalFilesScanned++;
        string fileName=dp->d_name;
        if(fileName=="."||fileName==".."||fileName=="...")  //. , .. , and ... are detected as directories while using dirent
            continue;
        string path=curDirFullPath+"/"+fileName;
        struct stat s;

        if( lstat(path.c_str(),&s) == 0 )
        {
            if( S_ISLNK(s.st_mode) )    //symbolic link similar to shortcut for folders; skip as will be scanned in original location and avoid scanning twice
                continue;

            else if( S_ISDIR(s.st_mode) ){  //it's a directory
                findLargestFiles(h,path);
            }

            else if( S_ISREG(s.st_mode) )  //it's a file
            {
                cout<<fileName<<endl;
                fileProperties temp;
                temp.fileName=fileName;
                temp.fileSize=s.st_size;
                if(temp.fileSize>h.getMinFileSize()){
                    h.extractMin();
                    h.insertKey(temp);
                }
            }

        }
        else    //error
            cout<<"error in using stat"<<endl;

}
closedir(dirp);
}

/**
    Code to find the largest 10 file in system finishes
 */


//driver program
int main()
{
/**
    Following driver program segment works to clean up the Desktop
 */
    stringvec seenExtensions;
    /*to find home path in linux(windows also???) automatically*/
    passwd* pw = getpwuid(getuid());
    string homePath(pw->pw_dir);
    organizeDesktop(homePath, seenExtensions);
    cout<<endl<<endl<<endl<<endl<<"**The desktop has been cleaned. Files moved to "<<homePath<<"/Documents/ **"<<endl<<endl<<endl;

/**
   Driver program segment to clean the desktop finishes.
   Driver program segment to find the top 10 files in the system starts
 */


    MinHeap h(10);

    //populate heap with 10 dummy values
    fileProperties temp;
    temp.fileName="abc";
    temp.fileSize=-1;
    for(int i=0;i<10;i++){
        h.insertKey(temp);
    }

    string mediaPath="/media";
    string mediaPath2=homePath;    //already found the home path in the code above

    cout<<"****Scanning to find largest files will start now. Press enter key TWICE to begin...****";
    cin.ignore().get();

    findLargestFiles(h,mediaPath);
    findLargestFiles(h,mediaPath2);

    cout<<endl<<endl<<"The 10 largest files in your system are:  "<<endl<<endl<<endl;
    for(int i=0;i<10;i++){
        fileProperties temps=h.extractMin();
    cout<<temps.fileName<<"        "<<temps.fileSize/(1000000)<<"MB"<<endl<<endl;;
    }

    cout<<endl<<endl<<endl<<"Total files scanned: "<<totalFilesScanned<< endl;

/**
    Driver program segment to find the largest 10 file in system finishes
 */


    return 0;


}
