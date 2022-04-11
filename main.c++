/*

Samuel Maina Wanjiru
COM/34/18
*/

/*libraries*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/*Declare your struct of type Movies here*/

struct Movie
{
    string genre, title, rating;
    int releaseYear;
    double playTimeInMinutes;
};

using namespace std;

int readTheStatedNumberOfRecords(ifstream &);
int readContentInArrayAndReturnNoOfRecordsRead(ifstream &, vector<Movie> &);
void displayMenu();
void getUserMenuSelectionAndPerformAction();
void promptForDatabaseClearance();
string readAValidFileName();

int main(int argc, char const *argv[])
{
    getUserMenuSelectionAndPerformAction();
    return 0;
}

class FileManipulator
{
public:
    FileManipulator(string fileName);
    static void setToFalseIsAnotherFileOpen();
    ~FileManipulator();
    void open();
    void close();
    void openToWrite();

public:
    // inFile and outFile are delete function which means that they can't be
    // returned as values through getters.
    ifstream inFile;
    ofstream outFile;

private:
    string fileName;
    inline static bool isAnotherFileOpen = false;
};

class Database
{
private:
    vector<Movie> movieArr;

public:
    Database();

    void loadData();
    void clearDatabase();
    void printDatabase();
    void printTotalRunTimeInHoursAndMinutes();
    void printMoviesByRating();
    void printMoviesSortedByYear();
    void exportMoviesByGenre();

    bool promptToLoadData();
};

Database::Database()
{
}

void Database::loadData()
{
    string fileName;

    fileName = readAValidFileName();

    char response;

    // prompt the user to have the current database  cleared if there is existing data in the database.
    if (movieArr.size() > 0)
    {
    }
    // the user does not want to clear hence no need to continue.
    if (response == 'n' || response == 'N')
        return;
    FileManipulator file = FileManipulator(fileName);

    file.open();
    int numberOfRecords = readTheStatedNumberOfRecords(file.inFile);
    int noOfrecordsRead = readContentInArrayAndReturnNoOfRecordsRead(file.inFile, movieArr);

    if (noOfrecordsRead != numberOfRecords)
    {
        cerr << "The record number recorded is not the same as the number of records in the file";
        exit(1);
    }
    file.close();
}
void Database::clearDatabase()
{
    if (movieArr.size() == 0)
    {
        cout << "Movie database already empty." << endl;
        return;
    }
    movieArr.clear();
}

void Database::printDatabase()
{
    cout << "The number of records = " << movieArr.size() << endl;
    for (const auto movie : movieArr)
    {
        cout << movie.genre << " ";
        cout << movie.title << " ";
        cout << movie.releaseYear << " ";
        cout << movie.playTimeInMinutes << " ";
        cout << movie.rating << " ";
        cout << endl;
    }
}

void Database::printTotalRunTimeInHoursAndMinutes()
{

    int totalMinutes = 0;
    for (const auto movie : movieArr)
    {
        totalMinutes += movie.playTimeInMinutes;
    }
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    cout << "Total run time : " << hours << " hrs " << minutes << " mins" << endl;
}

void Database::printMoviesByRating()
{
    string rating;
    if (promptToLoadData())
        return;
    string response;
    cout << "Enter the rating : ";
    cin >> response;

    cout << "Movie\t\tGenre" << endl;
    for (const auto movie : movieArr)
    {
        if (movie.rating == rating)
        {
            cout << movie.title << "\t\t" << movie.genre << endl;
        }
    }
}
void Database::printMoviesSortedByYear()
{
    if (promptToLoadData())
        return;
    int size = movieArr.size();
    sort(movieArr.begin(), movieArr.end(), [](const Movie &lhs, const Movie &rhs)
         { return lhs.releaseYear < rhs.releaseYear; });
    for (int i = 0; i < size; i++)
        cout << movieArr[i].releaseYear << " : " << movieArr[i].title << endl;
}

void Database::exportMoviesByGenre()
{
    string writeFiles[4] = {"drama.txt",
                            "action.txt",
                            "comedy.txt",
                            "scifi.txt"};

    if (promptToLoadData())
        return;
    for (const auto movie : movieArr)
    {
        if (movie.genre == "action")
        {

            FileManipulator file = FileManipulator(writeFiles[1]);
            file.openToWrite();
            file.outFile << movie.title << " (" << movie.releaseYear << ") " << endl;
            file.close();
        }
        else if (movie.genre == "drama")
        {

            FileManipulator file = FileManipulator(writeFiles[0]);
            file.openToWrite();
            file.outFile << movie.title << " (" << movie.releaseYear << ") " << endl;
            file.close();
        }
        else if (movie.genre == "comedy")
        {

            FileManipulator file = FileManipulator(writeFiles[2]);
            file.openToWrite();
            file.outFile << movie.title << " (" << movie.releaseYear << ") " << endl;
            file.close();
        }
        else if (movie.genre == "scifi")
        {

            FileManipulator file = FileManipulator(writeFiles[3]);
            file.openToWrite();
            file.outFile << movie.title << " (" << movie.releaseYear << ") " << endl;
            file.close();
        }
    }
}

bool Database::promptToLoadData()
{
    if (movieArr.size() == 0)
    {
        cout << "Load movie file first! Use option 1." << endl;
        return true;
    }
    return false;
}

int readTheStatedNumberOfRecords(ifstream &inFile)
{
    int numberOfRecords;
    inFile >> numberOfRecords;
    if (numberOfRecords < 1)
    {
        cerr << "The file does not have record number stated on it or ";
        cerr << "it does not have any records or the number stated may be negative." << endl;
        exit(EXIT_FAILURE);
    }
    return numberOfRecords;
}

int readContentInArrayAndReturnNoOfRecordsRead(ifstream &inFile, vector<Movie> &movieArr)
{
    int recordsCounter = 0;
    string line;

    // used to avoid the first record which contain the number of records.
    bool isFirst = true;

    while (getline(inFile, line))
    {
        if (!isFirst)
        {
            Movie movie;
            stringstream ss(line);
            getline(ss, movie.genre, ':');
            getline(ss, movie.title, ',');
            ss >> movie.releaseYear;
            ss >> movie.playTimeInMinutes;
            ss >> movie.rating;

            recordsCounter++;
            movieArr.push_back(movie);
        }
        isFirst = false;
    }

    return recordsCounter;
}

void displayMenu()
{
    cout << "===================================================== \n";
    cout << " \t\tMENU \t \n ";
    cout << "===================================================== \n";
    cout << " 1 - Laod Movie File\n";
    cout << " 2 - View Total Movie Database Runtime\n";
    cout << " 3 - View Movies by Rating \n";
    cout << " 4 - Export Movies by Genre \n";
    cout << " 5 - Clear Currently Loaded Database \n";
    cout << " 6 - Print Database Sorted by Year \n";
    cout << " Q or q - To Quit \n";
}

void getUserMenuSelectionAndPerformAction()
{
    enum choices
    {
        load = '1',
        runtime = '2',
        rating = '3',
        doExport = '4',
        clear = '5',
        sort = '6',
        qQuit = 'q',
        Qquit = 'Q'
    };

    char choice;

    Database db;

    do
    {
        displayMenu();
        cout << "Enter your choice :";
        cin >> choice;
        switch (choice)
        {
        case load:
            db.loadData();
            break;
        case runtime:
            db.printTotalRunTimeInHoursAndMinutes();
            break;
        case rating:
            db.printMoviesByRating();
            break;
        case doExport:
            db.exportMoviesByGenre();
            break;
        case clear:
            db.clearDatabase();
            break;

        case sort:
            db.printMoviesSortedByYear();
            break;

        // clear the  database before exiting the program.
        case qQuit:
            db.clearDatabase();
            return;
            break;
        case Qquit:
            db.clearDatabase();
            return;
            break;
        default:
            cout << "invalid choice \n";
            break;
        }

    } while (true);
}

string readAValidFileName()
{
    string inputFileName;
    while (true)
    {
        cout << "Enter the name of the file that you would like to read: ";
        cin >> inputFileName;
        if (cin.fail())
        {
            cin.clear();
            cout << "Please enter the name as a string.";
            cin >> inputFileName;
        }
        if (!cin.fail())
        {
            ifstream inFile;
            inFile.open(inputFileName);
            if (!inFile)
                cout << "The file does not exist in  the current directory or the file name or(and) the extension is wrong." << endl;
            else
                break;
        }
    }

    return inputFileName;
}

FileManipulator::FileManipulator(string fileName)
{
    this->fileName = fileName;
}
FileManipulator::~FileManipulator()
{
    inFile.close();
}
void FileManipulator::open()
{
    if (isAnotherFileOpen)
    {
        cerr << "Please close the " << fileName << " where it was opened" << endl;
        exit(EXIT_FAILURE);
    }
    inFile.open(fileName);
    if (!inFile)
    {
        cerr << "Unable to open the file " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    isAnotherFileOpen = true;
}

void FileManipulator::openToWrite()
{
    if (isAnotherFileOpen)
    {
        cerr << "Please close the " << fileName << " where it was opened" << endl;
        exit(EXIT_FAILURE);
    }
    outFile.open(fileName);
    if (!inFile)
    {
        cerr << "Unable to open the file " << fileName << endl;
        exit(EXIT_FAILURE);
    }
    isAnotherFileOpen = true;
}

void FileManipulator::close()
{

    inFile.close();
    outFile.close();
    isAnotherFileOpen = false;
}