#include "argh.h"
#include "process.h"

#include <string>
#include <iostream>

int main(int argc, char **argv) {

    // Handle CLI arguments
    handleArguments(argc, argv);

    for(auto &filename : args.filenames) {
        processFile(filename, args.isVerbose);
    }
}