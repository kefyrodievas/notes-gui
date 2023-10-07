#pragma once
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/imgui.h"
#include <cstring>
#include <dirent.h> 
#include <SDL2/SDL.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <vector>
#include "main.h"

std::vector<char*> get_files(char * dir);
char * init_buf();

struct window {
  int height, width;
};


class MainWindow{
  public:
    void draw_main_window(SDL_Window *);
    char* dir = working_dir();
    std::vector<char*> files = get_files(this->dir);
    private:
    char * buffer = init_buf();
    int * selected_note;
    int * item_count;
  
};

void MainWindow::draw_main_window(SDL_Window *window){
    // std::cout << this->dir << "\n";
    std::vector<char*> files = this->files;
    struct window MyWindow;
    SDL_GetWindowSizeInPixels(window, &MyWindow.width, &MyWindow.height);
    ImVec2 vec;
    vec.x = MyWindow.width;
    vec.y = MyWindow.height;
    ImGui::Begin("testing", (bool *)true,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetWindowSize(vec);
    ImGui::SetWindowPos(ImVec2(0, 0));
    // ImGui::InputText(" ");
    ImGui::InputTextMultiline(" ", this->buffer, 4096, ImVec2(vec.x*0.75, vec.y * 0.97));
    ImGui::SameLine(0.0f, 0.0f);
    
    // ImGui::ListBox(" ");
    // std::cout <<  << std::endl;
    if(ImGui::BeginListBox("##", ImVec2(vec.x*0.25, vec.y * 0.97))){
      for(int i = 0; i < files.size(); i++){
        ImGui::Selectable(files[i]);
        // std::cout << this->files[i] << "\n";
      }
      ImGui::EndListBox();
    }
    ImGui::SameLine();
    ImGui::Text(" ");
    ImGui::End();
    // rendering
    
}

std::vector<char*> get_files(char * directory){
  DIR *d;
  struct dirent *dir;
  char* file;
  std::vector<char*> dir_;
  d = opendir(directory);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if(strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") !=0){
        dir_.push_back(dir->d_name);
      }
      std::cout << dir->d_name << " ";
    }
    closedir(d);
  }
  return dir_;
}

char * init_buf(){
      char* ret = (char*)malloc(sizeof(char)*4096);
      memset(ret, 4096, sizeof(char));
      return ret;
}