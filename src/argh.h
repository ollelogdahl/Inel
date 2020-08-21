#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unistd.h>

const char *help =
"usage: inel [options] file...\n"
"options:\n"
"  -v                verbose.\n"
"  -h                Show help page.\n"
"  -c                Colorized output.\n"
"For more details see inel(x).";

const char *helpShort =
"usage: inel [options] file...\n"
"For more details see inel(x) or inel -h.";


struct ProgramArguments {
    std::vector<std::string> filenames;
    bool isVerbose;
    bool colorized;

    ProgramArguments() {};

    ProgramArguments(std::vector<std::string> fn, bool v, bool c)
    : filenames(fn), isVerbose(v), colorized(c) {};
} args;

ProgramArguments handleArguments(int argc, char **argv) {
    args = ProgramArguments();

    int opt;
    while((opt = getopt(argc, argv, "hvc")) != EOF) {
        switch(opt) {
            case 'v': args.isVerbose = true; break;
            case 'c': args.colorized = true; break;
            case 'h': 
                std::cout << help << std::endl; 
                exit(EXIT_SUCCESS);

            case '?':
                exit(EXIT_FAILURE);
        }
    }
    if (argv[optind] == NULL) {
        std::cout << "Mandatory file argument(s) missing." << std::endl;
        std::cout << helpShort << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = optind; i < argc; ++i) {
        args.filenames.push_back(argv[i]);
    }
}