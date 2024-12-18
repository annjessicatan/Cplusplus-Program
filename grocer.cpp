#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> // For numeric_limits to clear input buffer

using namespace std;

// Function prototypes for modular program design
void searchItemFrequency(const map<string, int>& items);
void printFrequencies(const map<string, int>& items);
void printHistogram(const map<string, int>& items);
map<string, int> processInputFile(const string& fileName);
void saveFrequenciesToFile(const map<string, int>& items, const string& outputFileName);

int main() {
    // Input and output file names
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    const string outputFileName = "frequency.dat";

    // Process input file and count item frequencies
    map<string, int> items = processInputFile(inputFileName);
    
    if (items.empty()) {
        // Error handling if file processing fails
        cout << "Error: Could not process input file or file is empty.\n";
        return 1; // Exit program with error code
    }

    // Save item frequencies to a backup file
    saveFrequenciesToFile(items, outputFileName);

    // Menu-driven program loop
    int choice;
    do {
        // Display menu options
        cout << "\n===== Corner Grocer Item Tracker =====\n";
        cout << "1. Search for item frequency\n";
        cout << "2. Display frequency of all items\n";
        cout << "3. Display histogram of item frequencies\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        
        cin >> choice;

        // Validate user input for numeric value
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue; // Restart the loop
        }

        // Handle menu options
        switch (choice) {
            case 1:
                // Search for the frequency of a specific item
                searchItemFrequency(items);
                break;
            case 2:
                // Display the frequency of all items
                printFrequencies(items);
                break;
            case 3:
                // Display a histogram of item frequencies
                printHistogram(items);
                break;
            case 4:
                // Exit the program
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                // Handle invalid menu selection
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4); // Continue until user chooses to exit

    return 0; // Program executed successfully
}

// Process the input file and return a map of item frequencies
map<string, int> processInputFile(const string& fileName) {
    map<string, int> items; // Map to store item frequencies
    ifstream inputFile(fileName); // Open input file for reading

    if (!inputFile.is_open()) {
        // Error handling if file cannot be opened
        cerr << "Error: Unable to open file " << fileName << ".\n";
        return items;
    }

    string item;
    while (inputFile >> item) {
        // Increment the frequency of each item in the map
        items[item]++;
    }

    inputFile.close(); // Close the file after reading
    return items; // Return the populated map
}

// Save item frequencies to a backup file
void saveFrequenciesToFile(const map<string, int>& items, const string& outputFileName) {
    ofstream outputFile(outputFileName); // Open output file for writing

    if (!outputFile.is_open()) {
        // Error handling if file cannot be created
        cerr << "Error: Unable to create file " << outputFileName << ".\n";
        return;
    }

    for (const auto& pair : items) {
        // Write each item and its frequency to the file
        outputFile << pair.first << " " << pair.second << endl;
    }

    outputFile.close(); // Close the file after writing
}

// Search for the frequency of a specific item
void searchItemFrequency(const map<string, int>& items) {
    string item;
    cout << "Enter the item to search: ";
    cin >> item; // Get the item name from the user

    auto it = items.find(item); // Look up the item in the map
    if (it != items.end()) {
        // Item found in the map
        cout << item << " was purchased " << it->second << " time(s).\n";
    } else {
        // Item not found in the map
        cout << item << " was not purchased today.\n";
    }
}

// Print the frequency of all items
void printFrequencies(const map<string, int>& items) {
    cout << "\nItem Frequencies:\n";
    for (const auto& pair : items) {
        // Print each item and its frequency
        cout << pair.first << ": " << pair.second << endl;
    }
}

// Print a histogram of item frequencies
void printHistogram(const map<string, int>& items) {
    cout << "\nItem Frequency Histogram:\n";
    for (const auto& pair : items) {
        // Print each item name followed by asterisks representing its frequency
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
}
