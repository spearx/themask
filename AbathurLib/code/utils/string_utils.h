#ifndef INC_STRING_UTILS
#define INC_STRING_UTILS

#include <vector>
#include <string>
#include "utils/json/json.h"
#include "utils/math/math.h"

typedef std::vector<std::string> VStrings;
typedef std::vector<float> VFloats;
typedef std::vector<int> VInts;

VStrings &split(const std::string &s, char delim, VStrings &elems);
VFloats &splitToFloats(std::string s, char delim, VFloats &elems);
VInts &splitToInts(std::string s, char delim, VInts &elems);
bool contains(const std::string &s, const std::string &f);

//Json utils
void     writeJson(Json::Value &root, const std::string &path, const std::string &value);
ColorF   getColorFromStr(const Json::Value &value, const ColorF &default_color);
Matrix44 getMatrixFromStr(const Json::Value &value, const Matrix44 &default_matrix);
Vector2  getVector2FromStr(const Json::Value &value, const Vector2 &default_vector);
Vector3  getVector3FromStr(const Json::Value &value, const Vector3 &default_vector);
Vector4  getVector4FromStr(const Json::Value &value, const Vector4 &default_vector);
float    getFloatFromStr(const Json::Value &value, const float &default_float);
bool     getBooleanFromStr(const Json::Value &value, const bool &default_bool);

#endif
