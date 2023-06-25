#include "GroceryItem.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <set>

using namespace std;

//Method to print a histogram of each item and associated quantity
//@param item - reference to constant set of Grocery Items
//@returns - NA
void printHistogram(const set<GroceryItem>& items) {
    for (const auto& item : items) {
        cout << item.getName() << " ";

        for (int i = 0; i < item.getQuantity(); i++) {
            cout << "*";
        }

        cout << endl;
    }
}

//Method to print each item plus the amount of times it appears on input list
//@param items - reference to constant set of Grocery Items
//@returns - NA
void printFrequencyList(const set<GroceryItem>& items) {
    for (const auto& item : items) {
        cout << item.getName() << " " << item.getQuantity() << endl;
    }
}

//Method to look up and display specific items details
//@param items - reference to constant set of Grocery Items
//@returns - NA
void lookUpItem(const set<GroceryItem>& items) {
    string itemName;
    cout << "Enter the item name: ";
    cin >> itemName;

    bool found = false;

    for (const auto& item : items) {
        if (item.getName() == itemName) {
            cout << itemName << " appears " << item.getQuantity() << " time(s) on the list." << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Item not found: " << itemName << endl;
    }
}

//Method that reads an input file and creates a set from the contents
//@param NA
//@returns - A set that includes GroceryItem objects (name and quantities)
set<GroceryItem> readInventoryFile() {
    ifstream inputFile("inventory.txt");

    if (!inputFile) {
        cerr << "Error opening file: inventory.txt" << endl;
        return {};
    }

    string name;

    // create our empty GroceryItem set
    set<GroceryItem> items;

    while (inputFile >> name) {
        GroceryItem* newItemPtr = new GroceryItem(name); // We create a pointer to a new GroceryItem object

        auto existingItem = items.find(*newItemPtr); // Check if the item already exists in the set using the pointer
        if (existingItem != items.end()) { // If the item is found we do work
            string existingName = existingItem->getName(); // Copy existing name
            int quantity = existingItem->getQuantity(); // Copy existing quantity
            items.erase(existingItem); // Erase item from the set
            newItemPtr = new GroceryItem(existingName, quantity); // Create new item with the copies we made of existingName/Quantity
        }

        newItemPtr->addItem(); // Increment quantity of the item
        items.insert(*newItemPtr); // Insert the dereferenced item into our set
        delete newItemPtr; // Free the memory of the newItem pointer

        // Back up after each loop for incremental backups
        ofstream outputFile("frequency.dat");
        if (!outputFile) {
            cerr << "Error opening file: frequency.dat" << endl;
            return items;
        }

        for (const auto& item : items) {
            outputFile << item.getName() << " " << item.getQuantity() << endl;
        }

        outputFile.close();
    }

    inputFile.close();

    return items;
}

//A method that provides our programs main menu
//@param NA
//@returns - NA
void mainMenu() {
    int choice = 0;
    const int LOOKUP_ITEM = 1;
    const int PRINT_FREQ_LIST = 2;
    const int PRINT_HIST = 3;
    const int EXIT_APP = 4;
    const string error = "Error: Please choose an number between 1 and 4.";
    bool exitProgram = false;
    string input;

    do {
        cout << "------ Main Menu ------" << endl;
        cout << LOOKUP_ITEM << ". Look up an item" << endl;
        cout << PRINT_FREQ_LIST << ". Print list with frequencies" << endl;
        cout << PRINT_HIST << ". Print histogram" << endl;
        cout << EXIT_APP << ". Exit" << endl;
        cout << "Enter your choice (1-4): ";

        getline(cin, input);

        try {
            choice = stoi(input);

            if (choice < 1 || choice > 4) {
                cerr << error << endl;
                continue;
            }
        }
        catch (const exception& e) {
            cerr << error << endl;
            continue;
        }

        // Read in input file and create our set AFTER our user makes their choice (ensuring we have the most up to date input file)
        set<GroceryItem> items = readInventoryFile();

        switch (choice) {
        case LOOKUP_ITEM:
            lookUpItem(items);
            break;
        case PRINT_FREQ_LIST:
            printFrequencyList(items);
            break;
        case PRINT_HIST:
            printHistogram(items);
            break;
        case EXIT_APP:
            cout << "Exiting the program!" << endl;
            exitProgram = true;
            break;
        }
      
        if (!exitProgram) {
            cout << "Press 'Enter' to return to the main menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    } while (!exitProgram);
}

int main() {
    mainMenu();
    return 0;
}
