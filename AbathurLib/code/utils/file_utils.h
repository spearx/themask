#ifndef INC_FILE_UTILS_H
#define INC_FILE_UTILS_H

#include <string>

bool existsFile(const char *filename);
size_t getFileSize(const char *filename);
std::string getPath(const std::string& str);
std::string getFilename(const std::string& str);
std::string getFilenameName(const std::string& str);

#endif // INC_FILE_UTILS_H