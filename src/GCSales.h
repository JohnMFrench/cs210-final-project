#include <string>
#include <vector>
#include <tuple>

#ifndef GC_SALES_H
#define GC_SALES_H

using namespace std;

class GCSalesClient
{
public:
    GCSalesClient(string inputFilename);
    int RunClient();
private:
    void PrintMenu();
    void PrintItems();
    void PrintHistogram();
    void RequestLookupItem();
    void RequestMenuSelection();
    int LookupItem(string itemName);
    string inputFilename;
    string outFilename;
    vector<tuple<string, int>> items;
};
#endif // GC_SALES_H
