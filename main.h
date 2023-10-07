#pragma once
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/imgui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

// #include <experimental/filesystem>
// namespace fs = std::filesystem;
void create_folder(){
    char * home = getenv("HOME");
    
    char * command = (char*)malloc(512*sizeof(char));
    memset(command, 0, 512);
    strcat(command, "mkdir -p ");
    strcat(home , "/.Notes");
    // char * final = (char*)malloc(strlen(command) + strlen)
    // std::cout << command << "\n" ;
    strcat(command, home);
    // std::filesystem::create_directory(strcat(home , "/.Notes"));
    system(command);
}

char * working_dir(){
    char * home = getenv("HOME");
    
    // strcat(home , "/.Notes");
    // std::cout << home;
    return home;
}


