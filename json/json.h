//
// Created by 34885 on 2023/3/18.
//

#ifndef JSONPARSERPROJECTFINAL_JSON_H
#define JSONPARSERPROJECTFINAL_JSON_H
#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
namespace Ty{
    namespace json{


class Json{
public:
    enum Type{  //枚举类定义json类型
        json_null = 0,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };
    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char * value);
    Json(const std::string & value);
    Json(Type type);
    Json(const Json & other);
    //重载类型转换运算符  使用类似 int a = v1这种时 将v1进行类型转换int(v1),我们重载这个运算符返回m_value中的int值。
    operator bool();
    operator int();
    operator double();
    operator string();
    operator string () const;

    bool isNull() const{
        return this->m_type==json_null;
    }
    bool isBool() const{
        return this->m_type==json_bool;
    }
    bool isInt() const{
        return this->m_type==json_int;
    }
    bool isDouble() const{
        return this->m_type==json_double;
    }
    bool isString() const{
        return this->m_type==json_string;
    }
    bool isArray() const{
        return this->m_type==json_array;
    }
    bool isObject() const{
        return this->m_type==json_object;
    }

    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    string asString() const;

    bool has(int index);
    bool has(const char * key);
    bool has(const string &key);

    void remove(int index);
    void remove(const char * key);
    void remove(string & key);
    Json & operator[](int index);
    void append(const Json & other);
    Json & operator[](const char * c);
    Json & operator[](const string &s);
    Json & operator = (const Json & other);
    string str() const;
    void copy(const Json & j);
    void clear();
    //定义json数组的迭代器
    typedef std::vector<Json>::iterator iterator;
    iterator begin(){
        return this->m_value.my_array->begin();
    }
    iterator end(){
        return this->m_value.my_array->end();
    }
//    bool operator != (const Json &other);
//    bool operator == (const Json &other);
//    bool operator == (bool value);
//    bool operator != (bool value);

    bool operator == (const Json & other);
    bool operator != (const Json & other);

    void parse(const string  & str);

private:
    union Value{   //联合体是公用的  其中 Value的大小由 其中内存占用最大的元素来决定
        bool m_bool;
        int m_int;
        double m_double;
        std::string * m_string; //存放string的指针
        std::vector<Json> * my_array;
        std::map<string,Json> * m_object; //用map存对象  对象都是kv键值对构成
    };
    Type m_type;
    Value m_value;
};


















    }
}
#endif //JSONPARSERPROJECTFINAL_JSON_H
