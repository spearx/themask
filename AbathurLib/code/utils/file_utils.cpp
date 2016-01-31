#include "file_utils.h"
#include <cstdio>

bool existsFile(const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (f) {
    fclose(f);
    return true;
  }
  return false;
}

size_t getFileSize(const char *filename) {
  size_t nbytes = 0;
  FILE *f = fopen(filename, "rb");
  if (f) {
    fseek(f, 0, SEEK_END);
    nbytes = ftell(f);
    fclose(f);
  }
  return nbytes;
}

std::string getPath(const std::string& str)
{
  std::size_t found = str.find_last_of("/\\");
  std::string path;
  if (found != std::string::npos) {
    path = str.substr(0, found);
  }
  path = path + "/";
  return path;
}

std::string getFilename(const std::string& str)
{
  std::size_t found = str.find_last_of("/\\");
  std::string filename = str.substr(found + 1);
  return filename;
}

std::string getFilenameName(const std::string& str)
{
  std::size_t found = str.find_last_of("/\\");
  std::string filename = str.substr(found + 1);
  std::size_t found_name = filename.find_last_of(".");
  std::string name = filename.substr(0, found_name);
  return name;
}
