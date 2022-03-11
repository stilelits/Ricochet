#ifndef UTILS_CPP_
#define UTILS_CPP_

#include <windows.h>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <map>
#include <math.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>

enum Direction {dirNull, dirUp, dirLeft, dirDown, dirRight};

#define SCREEN_PIXEL_WIDTH  (640)
#define SCREEN_PIXEL_HEIGHT (480)
#define FRAMERATE           (60)
#define FRAMELENGTHCLOCKS   (CLOCKS_PER_SEC / FRAMERATE)
#define FRAMELENGTHMILLIS   (1000 / FRAMERATE)
#define ONE_SECOND          (FRAMERATE)
#define EPSILON (.00001)
#define FLOATWITHIN(x,y,z)               (((x)-(y)>-(z))&&((x)-(y)<(z)))
#define FLOATEQUAL(x,y)                  (FLOATWITHIN(x,y,EPSILON))
#define FLOATLESS(x,y)                   ((x)+EPSILON<(y))
#define FLOATGREATER(x,y)                ((x)-EPSILON>(y))
#define FLOATGREATEROREQUAL(x, y)        (!FLOATLESS(x, y))
#define FLOATLESSOREQUAL(x, y)           (!FLOATGREATER(x, y))
#define VECTOR_FIND(vec,obj)             (std::find(vec.begin(), vec.end(), obj))
#define VECTOR_INDEX_OF(vec,obj)         (std::find(vec.begin(), vec.end(), obj) - vec.begin())
#define VECTOR_CONTAINS(vec,obj)         (VECTOR_FIND(vec,obj) != vec.end())
#define VECTOR_POINTER_CONTAINS(vec,obj) (VECTOR_POINTER_FIND(vec,obj) != vec->end())
#define VECTOR_REMOVE(vec,obj)           vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end())
#define VECTOR_POINTER_REMOVE(vec,obj)   vec->erase(std::remove(vec->begin(), vec->end(), obj), vec->end())

void normalize2dVector(float* x, float* y, float normTo);
std::vector<std::string> splitString(const std::string& original, const char* delim=" ");
std::vector<std::vector<std::string> > tokenize(const std::string& line);
std::string toStr(int x);
void popUp(const std::string& msg);
void popUp(int msg);
std::string toStr(bool x);
bool fileExists(const std::string& filePath);
std::string removeAll(const std::string& original, const std::string& toFind);
std::string replaceString(const std::string& str, const std::string& toReplace, const std::string& toInsert);
std::string toHex(int x);
std::string toStr(char x);
std::string toStr(float x);
//popUp(std::string(__FILE__) +":"+std::string(__FUNCTION__)+":"+toStr(__LINE__));
void popUp(float msg);
bool vectorContains(std::vector<void*> vec, void* toFind);
float parseFloat(const std::string& str);
bool parseBool(const std::string& str);
int parseInt(const std::string& str);
extern std::string g_folder;
bool isInt(const std::string& str);
std::string joinVector(const std::vector<std::string>& vec, const std::string& toInterleave = "");
std::string replaceAll(const std::string& original, const std::string& toFind, const std::string& toInsert);

#endif /* UTILS_CPP_ */
