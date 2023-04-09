#include <iostream>
#include <string>
#include <filesystem>

using namespace std;
using namespace std::filesystem;
using namespace chrono;
int fileCount = 0;


void deleteOldFilesL(string path, chrono::system_clock::time_point olderThanDate, string recurseornot)
{
    directory_iterator end_itr;
    cout << path << " 1010ccccccccccceeeeeee deleted" << endl;
    for (directory_iterator itr(path); itr != end_itr; ++itr)
    {
        cout << " vvvvvvccccccccccceeeeeee deleted" << endl;
        
        if (is_directory(itr->status()) && recurseornot == "yes")
        {
            
            deleteOldFilesL(itr->path().string(), olderThanDate, recurseornot);
            
        }
        else if (is_regular_file(itr->status()))
        {
            auto lastWriteTime = last_write_time(itr->path());
            
            try {
                struct stat result2;
                //char* c = const_cast<char*>(itr->path().string().c_str());
                if (stat(itr->path().string().c_str(), &result2) == 0)
                {
                    auto mod_time = result2.st_mtime;
                    auto age = chrono::duration_cast<chrono::seconds>(olderThanDate.time_since_epoch());
                   
                    if (mod_time < age.count())
                    {
                        remove(itr->path());
                        ++fileCount;
                        cout << "Delete " << itr->path().string()<< endl;
                    }

                }
            }
            catch (exception e) {
                cout << e.what() << endl;
            }
           
        }
        
    }
}


void deleteOldFiles(string path, int daysOld, string recurseornot)
{

    cout << "Deleting files older than " << daysOld << " days" << endl;
    deleteOldFilesL(path, chrono::system_clock::now() -  chrono::hours(24 * daysOld ) , recurseornot);
    cout << fileCount << " files deleted" << endl;
}


int main(int argc, char* argv[])
{
    string recurseornot = argc <= 2 ? "no" : argv[3];
    int result;
    //sscanf_s(argv[2], "%ld", &result);
    
    if (argc < 2 || !sscanf_s(argv[1], "%ld", &result) || !exists(argv[2]))
    {
        cout << "Usage: DeleteOldFiles daysOld path [recurse:yes|no]" << endl;
        return 1;
    }
    else
    {
        cout << "===========================" << endl;
        cout << "argv[2]" << endl;
        cout << argv[2] << endl;
        cout << "result" << endl;
        cout << result << endl;
        cout << "recurseornot" << endl;
        cout << recurseornot << endl;
        cout << "===========================" << endl;
        deleteOldFiles(argv[2], result, recurseornot);
        return 0;
    }
}