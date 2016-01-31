#include "string_utils.h"
#include <sstream>
#include <algorithm>
#include <string> 

bool replaceStr(std::string& str, const std::string& from, const std::string& to) {
  size_t start_pos = str.find(from);
  if (start_pos == std::string::npos)
    return false;
  while (start_pos != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos = str.find(from);
  }
  return true;
}

VStrings &split(const std::string &s, char delim, VStrings &elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

VFloats &splitToFloats(std::string s, char delim, VFloats &elems) {
  replaceStr(s, "\n", " ");
  replaceStr(s, "\r", " ");
  std::stringstream ss(s);
  std::string item;  
  while (std::getline(ss, item, delim)) {
    if (item != "") {
      float value = std::stof(item);
      elems.push_back(value);
    }
  }
  return elems;
}

VInts &splitToInts(std::string s, char delim, VInts &elems) {
  replaceStr(s, "\n", " ");
  replaceStr(s, "\r", " ");
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    if (item != "") {
      int value = std::stoi(item);
      elems.push_back(value);
    }
  }
  return elems;
}

bool contains(const std::string &str, const std::string &str2) {
  std::size_t found = str.find(str2);
  return (found != std::string::npos);
}

void writeJson(Json::Value &root, const std::string &path, const std::string &value) {
  std::string key = path;
  if (contains(key, "/")) { //key multiple
    VStrings keys;
    split(key, '/', keys);
    Json::Value &root_value = root;
    Json::Value *curr_value = &root_value;
    for (size_t i = 0; i < keys.size() - 1; ++i) {
      curr_value = &((*curr_value)[keys[i]]);
    }
    (*curr_value)[keys.back()] = value; //key value
    //root[keys[0]] = root_value;
  }
  else {
    root[key] = value;
  }
}

ColorF getColorFromStr(const Json::Value &value, const ColorF &default_color) {
  ColorF color(default_color);
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_color;
  VFloats fvalues;
  splitToFloats(str_value, ' ', fvalues);
  if (fvalues.size() == 3)
    color = ColorF(fvalues[0], fvalues[1], fvalues[2]);
  else if (fvalues.size() == 4)
    color = ColorF(fvalues[0], fvalues[1], fvalues[2], fvalues[3]);
  return color;
}

Matrix44 getMatrixFromStr(const Json::Value &value, const Matrix44 &default_matrix) {
  Matrix44 matrix(default_matrix);
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_matrix;
  VFloats v_floats;
  splitToFloats(str_value, ' ', v_floats);
  if (v_floats.size() == 16) {
    matrix.SetRow4(0, Vector4(v_floats[0], v_floats[1], v_floats[2], v_floats[3]));
    matrix.SetRow4(1, Vector4(v_floats[4], v_floats[5], v_floats[6], v_floats[7]));
    matrix.SetRow4(2, Vector4(v_floats[8], v_floats[9], v_floats[10], v_floats[11]));
    matrix.SetRow4(3, Vector4(v_floats[12], v_floats[13], v_floats[14], v_floats[15]));
  }
  return matrix;
}

Vector2 getVector2FromStr(const Json::Value &value, const Vector2 &default_vector)
{
  Vector2 vector(default_vector);
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_vector;
  VFloats v_floats;
  splitToFloats(str_value, ' ', v_floats);
  if (v_floats.size() == 2) {
    vector.x = v_floats[0];
    vector.y = v_floats[1];
  }
  return vector;
}

Vector3  getVector3FromStr(const Json::Value &value, const Vector3 &default_vector)
{
  Vector3 vector(default_vector);
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_vector;
  VFloats v_floats;
  splitToFloats(str_value, ' ', v_floats);
  if (v_floats.size() == 3) {
    vector.x = v_floats[0];
    vector.y = v_floats[1];
    vector.z = v_floats[2];
  }
  return vector;
}

Vector4  getVector4FromStr(const Json::Value &value, const Vector4 &default_vector)
{
  Vector4 vector(default_vector);
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_vector;
  VFloats v_floats;
  splitToFloats(str_value, ' ', v_floats);
  if (v_floats.size() == 4) {
    vector.x = v_floats[0];
    vector.y = v_floats[1];
    vector.z = v_floats[2];
    vector.w = v_floats[3];
  }
  return vector;
}

float getFloatFromStr(const Json::Value &value, const float &default_float) {
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_float;
  float fvalue = std::stof(str_value);
  return fvalue;
}

bool getBooleanFromStr(const Json::Value &value, const bool &default_bool)
{
  std::string str_value = value.asString();
  if (str_value.empty())
    return default_bool;
  
  std::transform(str_value.begin(), str_value.end(), str_value.begin(), ::tolower);
  if (str_value == "true" || str_value == "1" )
    return true;
  return false;
}