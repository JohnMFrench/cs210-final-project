#include "GCSales.h"

int main () {
    // declare input filename
    const string INPUT_FILENAME = "data/sales.txt";

    //instantiate new client
    GCSalesClient *gcsc = new GCSalesClient(INPUT_FILENAME);

    // run the program and return program's exit code
    return gcsc->RunClient();
}