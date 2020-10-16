/*
** EPITECH PROJECT, 2020
** arcade_temp
** File description:
** core
*/

#include <dlfcn.h>
#include <stdio.h>
#include <error.h>
#include <string>

#include "Core.hpp"

int main(int argc, char **argv) {
    if (argc != 2)
        error(84, 0, "Usage : ./arcade ${graphical library path}");
    std::string osef(argv[1]);
    Core a(osef);
    // void (*start)();

    // void *lib = NULL;
    // void *nibblerMain = NULL;
    // Nibbler nibblerHandler;

    // if ((lib = dlopen("games/nibbler/lib_arcade_nibbler.so", RTLD_LAZY)) == NULL)
    //     error(84, 0, "Can't open lib_arcade_nibbler.so");
    // if ((nibblerMain = dlsym(lib, "nibblerMain")) == NULL)
    //     error(84, 0, "Can't open Nibbler main");
    // nibblerHandler = (Nibbler)nibblerMain;
    // LibNibbler *myNibbler = nibblerHandler();
    // myNibbler->nibblerMain();
    // dlclose(lib);
    // return 0;
}
