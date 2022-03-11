/*
 * Utils.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: tr_dawson
 */

#include "Utils.h"

std::string g_folder;
std::string debugMsg="";
int debugVar=0;
float textSpeed = 100;
std::string toStr(int x){
 std::ostringstream stringMaker;
 stringMaker << x;
 return stringMaker.str();
}
void popUp(const std::string& msg){MessageBox(0, msg.c_str(), "Game Alert", MB_OK);}
void popUp(int msg){popUp(toStr(msg));}
std::string toStr(bool x){
 if(x){
  return "TRUE";
 }else{
  return "FALSE";
 }
}
std::string removeAll(const std::string& original, const std::string& toFind){
 std::string toInsert;
 return replaceAll(original,toFind,toInsert);
}
std::string replaceAll(const std::string& original, const std::string& toFind, const std::string& toInsert){
 return joinVector(splitString(original, toFind.c_str()), toInsert);
}
std::string joinVector(const std::vector<std::string>& vec, const std::string& toInterleave){
 std::string result;
 for (unsigned k=0;k<vec.size();k++){
  if (k > 0){result += toInterleave;}
  result += vec[k];
 }
 return result;
}
std::vector<std::string> splitString(const std::string& original, const char* delim){
 std::stringstream ss;
 ss.str(original);
 std::string item;
 std::vector<std::string> result;
 while (std::getline(ss,item,*delim)){
  result.push_back(item);
 }
 return result;
}
bool fileExists(const std::string& filePath){
 std::ifstream f(filePath.c_str());
 bool result=(f.good());
 f.close();
 return result;
}
std::string replaceString(const std::string& str, const std::string& toReplace, const std::string& toInsert){
 std::string result = str;
 std::string::size_type pos = 0;
 pos = result.find(toReplace,pos);
 if(pos!=std::string::npos){
  result.replace(pos,toReplace.length(),toInsert);
 }
 return result;
}
std::string toHex(int x){
 std::stringstream ss;
 ss << std::showbase << std::hex << x;
 return ss.str();
}
std::string toStr(float x){
 std::ostringstream stringMaker;
 stringMaker << x;
 return stringMaker.str();
}
std::string toStr(char x){
 std::ostringstream stringMaker;
 stringMaker << x;
 return stringMaker.str();
}
//very useful:
//popUp(std::string(__FILE__) +":"+std::string(__FUNCTION__)+":"+toStr(__LINE__));
void popUp(float msg){popUp(toStr(msg));}
float parseFloat(const std::string& str){
 std::stringstream ss;
 float result;
 ss<<str;
 ss>>result;
 return result;
}
bool parseBool(const std::string& str){
 bool result;
 if((str=="yes")||(str=="true")){
  result = true;
 } else {
  result = false;
 }
 return result;
}
std::string toStr(unsigned k){
 return toStr((int)k);
}
int parseInt(const std::string& str){
 std::stringstream ss;
 int result;
 if (str.find("0x")!=std::string::npos){
  ss<<std::hex<<str;
 } else {
  ss<<str;
 }
 ss>>result;
 return result;
}
float Q_rsqrt( float number ){
 long i;
 float x2, y;
 const float threehalfs = 1.5F;
 x2 = number * 0.5F;
 y  = number;
 i  = * ( long * ) &y;                       // evil floating point bit level hacking
 i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
 y  = * ( float * ) &i;
 y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
// y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
 return y;
}
void normalize2dVector(float* x, float* y, float normTo){
 float mult = normTo * Q_rsqrt((*x * *x) + (*y * *y));
 *x *= mult;
 *y *= mult;
}
bool isInt(const std::string& str){
 if (!str.size()){
  return false;
 } else {
  for (unsigned k=0; k < str.size(); k++){
   switch (str.at(k)){
   case '-': if (k>1){return false;}
   case '0':
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
   case '7':
   case '8':
   case '9':
    break;
   default: return false;
   }
  }
  return true;
 }
}
std::vector<std::vector<std::string> > tokenize(const std::string& line){
 std::vector<std::vector<std::string> > result;
 std::vector<std::string> toAdd;
 std::string token;
 bool inString = false;
 for(std::string::size_type i = 0; i < line.size(); i++) {
  switch (line[i]){
  case '_':
   if (inString){
    token += '\n';
   } else {
    token += line[i];
   }
   break;
  case '"':
   if (!toAdd.size()){toAdd.push_back("TEXTBOX");} //shorthand: if the first token starts out with quotes, it must be a TEXTBOX
   if (inString){
    toAdd.push_back(token);
    token.clear();
    inString = false;
   } else {
    if (token.size() > 0){ //not currently in a string, so treat it line any other token
     token += line[i];
    } else { //must be starting a string
     inString = true;
    }
   }
   break;
  case '<':
  case '>':
  case '=':
   if (token.size() > 0){
    toAdd.push_back(token);
    token.clear();
   }
   token = line[i];
   toAdd.push_back(token);
   token.clear();
   break;
  case ' ':
   if (inString){
    token += line[i];
   } else {
    if (token.size() > 0){
     toAdd.push_back(token);
     token.clear();
    }
   }
   break;
  case ':':
  case '\n':
  case '\r':
  case '\t':
   if (inString){
    token += line[i];
   } else {
    if (token.size() > 0){
     toAdd.push_back(token);
     token.clear();
    }
    if (toAdd.size() > 0){
     result.push_back(toAdd);
     toAdd.clear();
    }
   }
   break;
  default:
   token += line[i];
   if (!token.compare("//")){ //ignore everything else on the line
    token.clear();
    i = line.size(); //make this skip to the next newline
   }
   break;
  }
 }
 if (token.size() > 0){
  toAdd.push_back(token);
 }
 if (toAdd.size() > 0){
  result.push_back(toAdd);
 }
 return result;
}
