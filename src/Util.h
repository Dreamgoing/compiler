////
//// Created by 王若璇 on 16/12/16.
////
//
//#ifndef COMPILER_UTIL_HPP
//#define COMPILER_UTIL_HPP
//
//#include <string>
//#include <sstream>
//#include <utility>
//
//using namespace std;
/////#pragma once just like #ifndef #define #endif
////#pragma once
//
//pair<bool,int> mystringToInt(const string &str) noexcept(false) {
//    int res;
//    istringstream istr{str};
////    throw "exp";
//    if (!(istr >> res)) {
//        assert(0);
//        throw "type conversion failed";
//    }
//    return make_pair(istr.eof(), res);
//
//
//}
//
//pair<bool,double> mystringToDouble(const string &str) noexcept(false) {
//    double res;
//    istringstream istr{str};
//    if (!(istr >> res)) {
//        throw "type conversion failed";
//    }
//    return make_pair(istr.eof(), res);
//}
//
//#endif //COMPILER_UTIL_HPP
