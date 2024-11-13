/*
ReservationSystem.cpp
11/13/2024
Version 1.0
Carlos Alcala
*/

#include <iostream>
#include <cctype>
using namespace std;

// Function declarations (prototypes)
char **CreateArrayOfSeats (int NumberOfRows, int seats);
void InitializeSeats (char **ArrayOfSeats, int NumberOfRows, int seats);
void DisplayArrayOfSeats (char **ArrayOfSeats, int NumberOfRows, int seats, int seatsTaken, int totalSeats);
void MemoryCleanup (char **ArrayOfSeats, int NumberOfRows);
bool AreAllSeatsTaken(int seatsTaken, int totalSeats);

int main()
{
    char **ArrayOfSeats;
    int NumberOfRows, NumberOfSeats;
    char rowSelection;
    char seatSelection;
    int row, seat, seatsTaken = 0;
    
    cout << "Enter the number of rows: ";
    cin  >> NumberOfRows;
    cout << "Enter the number of seats on each row: ";
    cin  >> NumberOfSeats;

    ArrayOfSeats = CreateArrayOfSeats(NumberOfRows, NumberOfSeats);
    InitializeSeats(ArrayOfSeats, NumberOfRows, NumberOfSeats);
    
    int totalSeats = NumberOfRows * NumberOfSeats;
    DisplayArrayOfSeats(ArrayOfSeats, NumberOfRows, NumberOfSeats, seatsTaken, totalSeats);

    do
    {
        if (AreAllSeatsTaken(seatsTaken, totalSeats))
        {
            cout << "All seats are taken!" << endl;
            break;
        }
        
        cout << endl << "Enter a seat selection (example 5F -or- 00 to quit): ";
        cin  >> rowSelection >> seatSelection;
        
        if (rowSelection == '0')
            continue;

        seatSelection = toupper(seatSelection);
        row = rowSelection - '1';
        seat = seatSelection - 'A';

        if (row < 0 || row >= NumberOfRows || seat < 0 || seat >= NumberOfSeats)
        {
            cout << "Invalid seat selection. Please try again." << endl;
            continue;
        }

        if (ArrayOfSeats[row][seat] == '-')
        {
            cout << "Seat " << rowSelection << seatSelection << " is already taken." << endl;
        }
        else
        {
            ArrayOfSeats[row][seat] = '-';
            seatsTaken++;
            cout << "Seat " << rowSelection << seatSelection << " reserved successfully." << endl;
        }

        DisplayArrayOfSeats(ArrayOfSeats, NumberOfRows, NumberOfSeats, seatsTaken, totalSeats);

    } while (rowSelection != '0');

    cout << "Total seats reserved: " << seatsTaken << " out of " << totalSeats << endl;
    MemoryCleanup(ArrayOfSeats, NumberOfRows);

    return 0;
}

char **CreateArrayOfSeats (int NumberOfRows, int seats)
{
    char **ArrayOfSeats = new char*[NumberOfRows];
    for(int r = 0; r < NumberOfRows; r++)
        ArrayOfSeats[r] = new char[seats];
    return ArrayOfSeats;
}

void InitializeSeats (char **ArrayOfSeats, int NumberOfRows, int seats)
{
    for (int r = 0; r < NumberOfRows; r++)
    {
        for (int s = 0; s < seats; s++)
            ArrayOfSeats[r][s] = 'A' + s;
    }
}

void DisplayArrayOfSeats (char **ArrayOfSeats, int NumberOfRows, int NumberOfSeats, int seatsTaken, int totalSeats)
{
    cout << "\nSeating Chart:\n";
    for (int r = 0; r < NumberOfRows; r++)
    {
        cout.width(2);
        cout << r + 1 << ' ';
        for (int s = 0; s < NumberOfSeats; s++)
            cout << ArrayOfSeats[r][s] << ' ';
        cout << endl;
    }
    cout << "Total Seats: " << totalSeats << ", Seats Occupied: " << seatsTaken << endl;
}

void MemoryCleanup (char **ArrayOfSeats, int NumberOfRows)
{
    for (int r = 0; r < NumberOfRows; r++)
        delete [] ArrayOfSeats[r];
    delete [] ArrayOfSeats;
}

bool AreAllSeatsTaken(int seatsTaken, int totalSeats)
{
    return seatsTaken == totalSeats;
}
