//
// Created by 34885 on 2023/3/18.
//
#include "json.h"
#include <sstream>
#include <iostream>
#include <Parser.h>
using namespace Ty::json;

void Json::copy(const Json &other) {
    this->m_type = other.m_type;
    switch (this->m_type) {
        case json_null:
            break;
        case json_bool:
            this->m_value.m_bool = other.m_value.m_bool;
            break;
        case json_int:
            this->m_value.m_int = other.m_value.m_int;
            break;
        case json_double:
            this->m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            this->m_value.m_string = new string(*other.m_value.m_string);
            break;
        case json_array:
            this->m_value.my_array = new vector<Json>(*other.m_value.my_array);
            break;
        case json_object:
            this->m_value.m_object = new map<string,Json>(*other.m_value.m_object);
            break;
        default:
            break;
    }
}
Json::Json():m_type(json_null) { //初始化列表

}

Json::Json(bool value):m_type(json_bool) {
    this->m_value.m_bool = value;
}

Json::Json(int value):m_type(json_int){
    this->m_value.m_int = value;
}
Json::Json(double value) :m_type(json_double){
    this->m_value.m_double = value;
}
Json::Json(const char *value):m_type(json_string) {
    this->m_value.m_string = new string(value);
}
Json::Json(const std::string &value):m_type(json_string) {
    this->m_value.m_string = new string(value);
}

Json::Json(Type type) :m_type(type){
    switch (this->m_type) {
        case json_null:
            break;
        case json_bool:
            this->m_value.m_bool = false;
            break;
        case json_int:
            this->m_value.m_int = 0;
            break;
        case json_double:
            this->m_value.m_double = 0.0;
            break;
        case json_string:
            this->m_value.m_string = new string("");
            break;
        case json_array:
            this->m_value.my_array = new vector<Json>();
            break;
        case json_object:
            this->m_value.m_object = new map<string,Json>();
            break;
        default:
            break;
    }
}

Json::Json(const Json &other):m_type(other.m_type) {
    this->copy(other);
//    switch (this->m_type) {
//        case json_null:
//            break;
//        case json_bool:
//            this->m_value.m_bool = other.m_value.m_bool;
//            break;
//        case json_int:
//            this->m_value.m_int = other.m_value.m_int;
//            break;
//        case json_double:
//            this->m_value.m_double = other.m_value.m_double;
//            break;
//        case json_string:
//            this->m_value.m_string = other.m_value.m_string;
//            break;
//        case json_array:
//            this->m_value.my_array = other.m_value.my_array;
//            break;
//        case json_object:
//            this->m_value.m_object = other.m_value.m_object;
//            break;
//        default:
//            break;
//    }
}
//类型强制转换运算符是单目运算符，也可以被重载，但只能重载为成员函数，不能重载为全局函数。经过适当重载后，
// (类型名)对象这个对对象进行强制类型转换的表达式就等价于对象.operator 类型名()，即变成对运算符函数的调用。
Json::operator bool() {
    if(this->m_type!=json_bool){
        throw  logic_error("type error, not bool value");
    }
    return this->m_value.m_bool;
}

Json::operator int() {
    if(this->m_type!=json_int){
        throw  logic_error("type error, not int value");
    }
    return this->m_value.m_int;
}

Json::operator double() {
    if(this->m_type!=json_double){
        throw  logic_error("type error, not double value");
    }
    return this->m_value.m_double;
}

Json::operator string() {
    if(this->m_type!=json_string){
        throw  logic_error("type error, not string value");
    }
    return *(this->m_value.m_string);
}

Json & Json::operator[](int index) {
    //如果不是json array,要在json的m_type改为array并开辟内存空间
    if(m_type!=json_array){
        this->m_type = json_array;
        this->m_value.my_array = new vector<Json>();
    }
    if(index<0){
        throw logic_error("array[] index < 0");
    }
    size_t size = this->m_value.my_array->size();
    //因为要保证下标访问，所以不能用alloc 或者 resize的申请空间
    // 因为那样的内存未被初始化，所以我们直接插入n个初始化的Json以支持下标访问
    if(index>=size){
        for(size_t i = size;i<=index;i++){
            this->m_value.my_array->push_back(Json());
        }
    }
    return this->m_value.my_array->at(index);
}

Json & Json::operator[](const char * c) {
    string name(c);
    return (*(this))[name];
}

Json &Json::operator[](const string &s) {
    //json["bool"]是往json_object中的bool类型中，插值，并不是往m_value.m_bool中插值，
    // 所以如果m_type不是object类型，必须要改为object类型并new 一片内存空间出来
    if(this->m_type!=json_object){
        this->clear();
        this->m_type = json_object;
        this->m_value.m_object = new map<string,Json>();
    }
    return (*(this->m_value.m_object))[s];
}

Json &Json::operator=(const Json &other) {
    this->copy(other);
//    this->m_type = other.m_type;
//    switch (this->m_type) {
//        case json_null:
//            break;
//        case json_bool:
//            this->m_value.m_bool = other.m_value.m_bool;
//            break;
//        case json_int:
//            this->m_value.m_int = other.m_value.m_int;
//            break;
//        case json_double:
//            this->m_value.m_double = other.m_value.m_double;
//            break;
//        case json_string:
//            this->m_value.m_string = other.m_value.m_string;
//            break;
//        case json_array:
//            this->m_value.my_array = other.m_value.my_array;
//            break;
//        case json_object:
//            this->m_value.m_object = other.m_value.m_object;
//            break;
//        default:
//            break;
//    }
    return *this;
}

void Json::append(const Json &other) {
    if(m_type!=json_array){
        this->clear();
        this->m_type = json_array;
        this->m_value.my_array = new vector<Json>();
    }
    (this->m_value.my_array)->push_back(other);
}

string Json::str() const {
    stringstream ss;
    switch (this->m_type) {
        case json_null:
            ss << "null";
            break;
        case json_bool:
            if(this->m_value.m_bool){
                ss << "true";
            } else{
                ss << "false";
            }
            break;
        case json_int:
            ss << this->m_value.m_int;
            break;
        case json_double:
            ss << this->m_value.m_double;
            break;
        case json_string:
            ss << '\"' << *(this->m_value.m_string) << '\"';
            break;
        case json_array:{
            ss <<'[';
            for (auto it = this->m_value.my_array->begin();it!=this->m_value.my_array->end();it++){
                if(it!=this->m_value.my_array->begin()){
                    ss << ",";
                }
                ss <<it->str();  //递归调用 如果还碰到array就继续进一步深入去解析
            }
            ss << ']';
            break;
        }
        case json_object:
            ss <<'{';
            for (auto it = this->m_value.m_object->begin();it!=this->m_value.m_object->end();it++){
                if(it!=this->m_value.m_object->begin()){
                    ss << ",";
                }
                ss << '\"' << it->first <<'\"'<<":"<< it->second.str();  //递归调用 如果还碰到array就继续进一步深入去解析
            }
            ss << '}';
            break;
        default:
            break;
    }
    return ss.str();
}

void Json::clear() {
    switch (this->m_type) {
        case json_null:
            break;
        case json_bool:
            this->m_value.m_bool = false;
            break;
        case json_int:
            this->m_value.m_int = 0;
            break;
        case json_double:
            this->m_value.m_double = 0.0;
            break;
        case json_string:
        {
            delete this->m_value.m_string;
            break;
        }
        case json_array:
        {
            for(auto it:*this->m_value.my_array){
                it.clear();
            }
            delete  this->m_value.my_array;
            break;
        }
        case json_object:
        {
            for(auto it:*this->m_value.m_object){
                it.second.clear();
            }
            delete this->m_value.m_object;
            break;
        }
        default:
            break;
    }
    this->m_type = json_null;
}

bool Json::operator==(const Json &other) {
    if(this->m_type!=other.m_type){
        return false;
    }
    switch(this->m_type){
        case  json_null:
            return true;
        case json_bool:
            return this->m_value.m_bool==other.m_value.m_bool;
        case json_int:
            return this->m_value.m_int==other.m_value.m_int;
        case json_double:
            return this->m_value.m_double==other.m_value.m_double;
        case json_string:
            return *(this->m_value.m_string)==*(other.m_value.m_string);
        case json_array:
            if(this->m_value.my_array->size()!=other.m_value.my_array->size()){
                return false;
            }
            for(int i = 0;i<this->m_value.my_array->size();i++){
                if((*(this->m_value.my_array))[i].m_type!=(*(other.m_value.my_array))[i].m_type){
                    return false;
                }
                if((*(this->m_value.my_array))[i]!=(*(other.m_value.my_array))[i]){
                    return false;
                }
            }
            return true;
        case json_object:
            if(this->m_value.m_object->size()!=other.m_value.m_object->size()){
                return false;
            }
            for(auto it:*(this->m_value.m_object)){
                auto it2 = other.m_value.m_object->find(it.first);
                if(it2==other.m_value.m_object->end()){
                    return false;
                }
                if(it.second!=it2->second){
                    return false;
                }
            }
            return true;
        default:
            break;
    }
    return false;
}

bool Json::operator!=(const Json &other) {
    return ! ((*this)==other);
}

bool Json::asBool() const {
    if(this->m_type!=json_bool){
        throw logic_error("type error,not bool value");
    }
    return this->m_value.m_bool;
}

int Json::asInt() const {
    if(this->m_type!=json_int){
        throw logic_error("type error,not int value");
    }
    return this->m_value.m_int;
}

double Json::asDouble() const {
    if(this->m_type!=json_double){
        throw logic_error("type error,not double value");
    }
    return this->m_value.m_double;
}

string Json::asString() const {
    if(this->m_type!=json_string){
        throw logic_error("type error,not string value");
    }
    return *(this->m_value.m_string);
}

bool Json::has(int index) {
    if(this->m_type!=json_array){
        return false;
    }
    int size = this->m_value.my_array->size();
    return (index>=0 && index<size);
}

bool Json::has(const char * key) {
    if(this->m_type!=json_object){
        return false;
    }
    return m_value.m_object->find(string(key))!=m_value.m_object->end();
}

bool Json::has(const string &key) {
    if(this->m_type!=json_object){
        return false;
    }
    return m_value.m_object->find(key)!=m_value.m_object->end();
}

void Json::remove(int index) {
    if(this->m_type!=json_array){
        return;
    }
    if(this->has(index)){
        (*(this->m_value.my_array))[index].clear();
        this->m_value.my_array->erase(this->m_value.my_array->begin()+index);
    }
}

void Json::remove(string &key) {
    if(this->m_type!=json_object){
        return;
    }
    if(this->has(key)){
        (*(this->m_value.m_object))[key].clear();
        this->m_value.m_object->erase(key);
    }
}

void Json::remove(const char *key) {
    string name(key);
    remove(name);
}

void Json::parse(const string &str) {
    Parser p;
    p.load(str);
    *this = p.parse();
}



