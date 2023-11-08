//
// Created by 34885 on 2023/3/21.
//

#ifndef JSONPARSERPROJECTFINAL_PARSER_H
#define JSONPARSERPROJECTFINAL_PARSER_H
#pragma once
#include <string>
#include "json.h"
namespace Ty{
    namespace json{


class Parser{
public:
    Parser();
    void load(const std::string &str);
    Json parse();
private:
    std::string m_str;
    int m_index;
    void skip_white_space();
    char get_next_token();
    Json parse_null();

    Json parse_bool();
    std::string parse_string();
    Json parse_number();
    Json parse_array();
    Json parse_object();

};






    }
}
#endif //JSONPARSERPROJECTFINAL_PARSER_H
