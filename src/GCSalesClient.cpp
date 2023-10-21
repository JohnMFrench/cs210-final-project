#include "GCSales.h"

#include <iostream>  // printing to screen
#include <fstream>   // reading input file
#include <algorithm> // sorting item list
#include <iomanip>   // histogram printing

using namespace std;

GCSalesClient::GCSalesClient(string inputFilename)
{
    // declare variables for file parsing
    ifstream inFS;
    ofstream outFS;
    string line;

    // open input file
    inFS.open(inputFilename);

    // iterate until the EOF is reached
    while (!inFS.eof())
    {
        // read next line
        getline(inFS, line);

        // iterate through items list and search for line item
        bool itemInList = false;
        for (tuple<string, int> &item : items)
        {
            if (get<0>(item) == line)
            {
                // increment count of item
                get<1>(item) += 1;
                itemInList = true;
            }
        }
        // if item was not matched to list, add it
        if (!itemInList)
        {
            tuple<string, int> newItem = {line, 1};
            items.push_back(newItem);
        }
    }

    // close input filestream
    inFS.close();

    // write the item frequencies to the output file
    outFS.open("data/frequency.dat");
    for (tuple<string, int> item : items) {
        outFS << get<0>(item) << " " << get<1>(item) << endl;
    }
    outFS.close();
}

int GCSalesClient::LookupItem(string itemName)
{
    for (tuple<string, int> &item : items)
    {
        int min_length = std::min(get<0>(item).size(), itemName.size());
        if (get<0>(item).size() != itemName.size())
        {
            continue;
        }

        // use flag variable to record whether it has match
        bool matches_name = true;
        for (int i = 0; i < min_length; ++i)
        {
            // if caps-insensitive match is found, break from loop
            if (toupper(get<0>(item).at(i)) != toupper(itemName.at(i)))
            {
                matches_name = false;
                break;
            }
        }
        // if match was found, print and return success code
        if (matches_name)
        {
            cout << get<0>(item) << " " << get<1>(item) << endl;
            return 0;
        }
        continue;
    }
    // if the for loop ran all the way through,
    // no match was found, e.g. return 1 for error
    return 1;
}

// only prints menu options
void GCSalesClient::PrintMenu()
{
    cout << "1) View Single Item Sales" << endl;
    cout << "2) View All Item Sales" << endl;
    cout << "3) View Item Sales Histogram" << endl;
    cout << "4) Quit" << endl;
}

void GCSalesClient::PrintItems()
{
    // iterate through items and output name, count
    for (tuple<string, int> item : items)
    {
        cout << get<0>(item) << " " << get<1>(item) << endl;
    }
}

void GCSalesClient::PrintHistogram()
{
    const int CELL_WIDTH = 15;
    // implement lambda sort based on this example on stack overflow
    // https://stackoverflow.com/a/5123582
    sort(items.begin(), items.end(), [](const tuple<string, int> &lhs, const tuple<string, int> &rhs)
         {
             return get<1>(lhs) > get<1>(rhs); // use gt to sort descending
         });
    // iterate through item list to print histogram row
    for (const tuple<string, int> item : items)
    {
        // print item name right aligned
        cout << setw(CELL_WIDTH) << right << get<0>(item);
        // fill with fill char
        cout << setw(get<1>(item)) << left << setfill(char(177)) << char(177) << " (" << get<1>(item) << ")";
        cout << setfill(' ') << endl;
    }
}

void GCSalesClient::RequestLookupItem()
{
    // display menu for the lookup item function
    string userSelection;
    while (userSelection != "menu")
    {
        cout << "Enter item name or 'menu' to go back:";

        // read from user input and lookup item, it will print details if found
        getline(cin, userSelection);
        int lookupResult = this->LookupItem(userSelection);
        if (lookupResult == 1)
        {
            cout << userSelection << " could not be found" << endl;
        }
    }
}

int GCSalesClient::RunClient()
{
    char menuSelection;

    try
    {
        // run until menu option 4 selected
        while (menuSelection != '4')
        {
            this->PrintMenu();
            cout << "Enter menu selection :";
            cin >> menuSelection;
            cin.ignore(); // clear cin
            switch (menuSelection)
            {
            case '1':
                this->RequestLookupItem();
                break;
            case ('2'):
                this->PrintItems();
                break;
            case ('3'):
                this->PrintHistogram();
                break;
            case ('4'):
                cout << "Goodbye" << endl;
                break;
            default:
                cout << "Did not recognise input of " << menuSelection << endl;
            }
        }
    }
    catch (exception &ex)
    {
        cout << "GCSales Client encountered error:" << endl;
        cout << ex.what();
        return 1;
    }

    return 0;
}
