#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

int main()
{

    const char *filename = "sample.txt";
    string line;

    ofstream fout;
    fout.open(filename);

    if (!fout.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing." << endl;
        return 1;
    }

    cout << "--- Entering Write Mode ---" << endl;
    cout << "Enter lines of text to write to '" << filename << "'. Enter 'QUIT' on a new line to stop." << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (getline(cin, line))
    {
        if (line == "QUIT")
        {
            break;
        }

        fout << line << endl;
    }

    fout.close();
    cout << "\nData successfully written to '" << filename << "' and file closed." << endl;

    ifstream fin;
    fin.open(filename);

    if (!fin.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for reading." << endl;
        return 1;
    }

    cout << "\n--- Reading Data Back from File ---" << endl;

    while (getline(fin, line))
    {

        cout << line << endl;
    }

    fin.close();
    cout << "\nEnd of file content. File closed." << endl;

    return 0;
}