#pragma once
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_sdl2.h"
#include "imgui/imgui.h"
#include "main.h"
#include <SDL2/SDL.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <vector>

std::vector<char *> get_files(char *dir);
char *init_buf(size_t size_var, size_t size);
void create_file(char *file_name);

// TODO:
// Replace std::vector with another implementation;
// fix directory reading;
// implement file reading (C style);
// ditch C++ stdlib;
// fix file name buffer reset

struct window {
  int height, width;
};

class MainWindow {
public:
  void draw_main_window(SDL_Window *);
  char *dir = working_dir();
  std::vector<char *> files /* = get_files(this->dir)*/;

private:
  int f_len = strlen(this->dir) + 256;
  char *buffer = init_buf(sizeof(char), 4096);
  int *selected_note;
  int *item_count;
  char *file_name = init_buf(sizeof(char), 256);
  char *file_dir = init_buf(sizeof(char), f_len);
};

void MainWindow::draw_main_window(SDL_Window *window) {
  files = get_files(dir); // need to fix, very inefficient - reading the entire
                          // directory every frame is bad
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
  ImGui::Columns(2, NULL, false);
  ImGui::SetColumnWidth(0, vec.x * 0.75);
  ImGui::InputTextMultiline("##text_input", this->buffer, 4096,
                            ImVec2(vec.x * 0.74, vec.y - 17));
  ImGui::NextColumn();
  ImGui::Button("Open");
  ImGui::SameLine(0.0f, 0.0f);
  if (ImGui::Button("Add")) {
    if (strcmp(file_name, "") == 0)
      ;
    else {
      strcpy(file_dir, dir);
      strcat(file_dir, "/");
      strcat(file_dir, file_name);
      create_file(file_dir);
      memset(file_dir, 0, f_len * sizeof(char));

      // file_name = {0}; // WHY DOES THIS CRASH THE ENTIRE THING
      // this only sets the buffer to 0
      free(file_name);
      file_name = init_buf(sizeof(char), 256);
      // this is awful need to find a replacement for this
      //(no repeated allocation)
    }
  }
  ImGui::SameLine(0.0f, 0.0f);
  ImGui::Button("Delete");
  ImGui::PushItemWidth(vec.x * 0.25);
  ImGui::InputText("##file_input", this->file_name, 256);
  if (ImGui::BeginListBox("##list", ImVec2(vec.x * 0.25, vec.y - 62))) {
    for (int i = 0; i < this->files.size(); i++) {
      ImGui::Selectable(this->files[i]);
    }
    ImGui::EndListBox();
  }
  ImGui::End();
}

std::vector<char *> get_files(char *directory) {
  DIR *d;
  struct dirent *dir;
  std::vector<char *> dir_;
  d = opendir(directory);
  if (d) {
    while ((dir = readdir(d))) {
      if (dir == NULL) {
        break;
      }
      if (strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".") != 0) {
        dir_.push_back(dir->d_name);
      }
    }
    closedir(d);
  }
  return dir_;
}

char *init_buf(size_t size_var, size_t size) {
  char *ret = (char *)malloc(size * size_var);
  memset(ret, 0, size * size_var);
  return ret;
}

void create_file(char *file_name) {
  FILE *fptr;
  fptr = fopen(file_name, "a");
  fclose(fptr);
}

char *read_file(char *file) {
  FILE *fptr;
  fptr = fopen(file, "r");
  char *ret = (char *)malloc(4096 * sizeof(char));
  fgets(ret, 4096, fptr);
  fclose(fptr);
  return ret;
}