// Code get the name and number of miles runners ran each day from a data file. Finds the total average number of
//  miles for each runner, and write a report showing the daily, average, and total miles ran for each runner.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;


const int MAXROWS = 50;
const int NCOLS = 7;
const string fileName = "runners.txt";


// The function opens and reads the file and puts names into a 1D array, and miles into a 2D array
// Preconditions: Gets names and miles arrays from file and will empty original row which is capacity
// Postconditions: Gives the true number of rows found in the file, store the data from the file in the arrays in memory
int getMilesRan(string names[], double miles[][NCOLS], int MaxRows);

// Function finds the average miles and total miles of each runner
// Preconditions: Gets a table of miles for each day per runner and the number of runners
// Postcondition: Gives average miles ran and total miles in a week which is calculated and placed in the averages and total list
void calcTotalAverages(double miles[][NCOLS], double averages[], double total[], int numRows);

// Function writes a report showing the average miles and total miles ran for each runner
// Preconditions: Receives the names, the averages, and totals
// Postcondition: A formatted report is sent to the display
void createReport(string names[], double miles[][NCOLS], double total[], double averages[], int numRecords);



int main()
{

    string runners[MAXROWS];
    double milesRan[MAXROWS][NCOLS];
    double averages[MAXROWS];
    double total[MAXROWS];
    int numRecords;

    numRecords = getMilesRan(runners, milesRan, MAXROWS);
    calcTotalAverages(milesRan, total, averages, numRecords);

    createReport(runners, milesRan, total, averages, numRecords);

    return 0;
}

// Function reads runners data off a file
// Preconditions: Gets names and miles arrays from file and will empty original row which is capacity
// Postconditions: Gives the true number of rows found in the file, store the data from the file in the arrays in memory
int getMilesRan(string names[], double miles[][NCOLS], int MaxRows)
{
    ifstream inFile;
    int rows = 0;
    inFile.open(fileName);
    if (!inFile.is_open())
    {
        cout << "Could not open file\n";
        return -1;
    }

    inFile >> names[rows];
    while (!inFile.eof() && !(rows >= MaxRows))
    {
        for (int i = 0; i < NCOLS; i++)
        {
            inFile >> miles[rows][i];
        }
        rows++;
        inFile >> names[rows];
    }
    inFile.close();
    return rows;
}

// Function finds the average miles and total miles of each runner
//Preconditions: Gets a table of miles for each day per runner and the number of runners
//Postcondition: Gives average miles ran and total miles in a week which is calculated and placed in the averages and total list
void calcTotalAverages(double miles[][NCOLS], double total[], double averages[], int numRows)
{
    double sum = 0;
    for (int i = 0; i < numRows; i++)
    {
        sum = 0;
        for (int j = 0; j < NCOLS; j++)
            sum += miles[i][j];
        averages[i] = sum / (NCOLS);
        total[i] = sum;
    }
}

// Function writes a report showing the average miles and total miles ran for each runner
// Precondtions: Receives the names, the averages, and totals
// Postcondition: A formatted report is sent to the display
void createReport(string names[], double miles[][NCOLS], double total[], double averages[], int numRecords)
{
    cout << fixed << setprecision(2) << showpoint;
    cout << "Runner      Sun       Mon       Tue       Wed       Thr       Fri       Sat       Total      Average" << endl;
    for (int i = 0; i < numRecords; i++)
    {
        cout << setw(11) << left << names[i] << " ";
        for (int j = 0; j < NCOLS; j++)
            cout << setw(5) << miles[i][j] << setw(5) << " ";
        cout << setw(8) << total[i] << " ";
        cout << setw(7) << right << averages[i] << endl;
    }
}
