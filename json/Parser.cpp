#include "Parser.h"
#include "json.h"
using namespace Ty::json;

Parser::Parser():m_str(""),m_index(0) {

}

void Parser::load(const std::string &str) {
    this->m_str = str;
    this->m_index = 0;
}

Json Parser::parse() {
    char ch = get_next_token();
    switch (ch) {
        case 'n':
            this->m_index--;
            return parse_null();
        case 't':
        case 'f':
            this->m_index--;
            return parse_bool();
        case '-':
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
            this->m_index--;
            return parse_number();
        case '"':
            return Json(parse_string());
        case '[':
            return parse_array();
        case '{':
            return parse_object();
        default:
            break;
        throw logic_error("unexpected char");
    }
    return Json();
}


void Parser::skip_white_space() {
    while(this->m_str[this->m_index]==' '||this->m_str[this->m_index]=='\n'||this->m_str[this->m_index]=='\r'||this->m_str[this->m_index]=='\t'){
        this->m_index++;
    }
}

char Parser::get_next_token() {
    skip_white_space();
    char ch = this->m_str[this->m_index];
    this->m_index++;
    return ch;
}

Json Parser::parse_null() {
    if(this->m_str.compare(this->m_index,4,"null")==0){
        this->m_index+=4;
        return Json();
    }
    throw logic_error("parse null error");
}

Json Parser::parse_bool() {
    if(this->m_str.compare(this->m_index,4,"true")==0){
        this->m_index+=4;
        return Json(true); //有参构造函数，调用参数为bool的构造函数，在json.cpp中。
    }if(this->m_str.compare(this->m_index,5,"false")==0){
        this->m_index+=5;
        return Json(false); //有参构造函数，调用参数为bool的构造函数，在json.cpp中。
    }
    throw logic_error("parse bool error");
}

Json Parser::parse_number() {
    int pos = this->m_index;
    if(this->m_str[this->m_index]=='-'){
        this->m_index++;
    }
    if(this->m_str[this->m_index]<'0'||this->m_str[this->m_index]>'9'){
        throw logic_error("parse number error");
    }
    //如果是0到9就继续往后挪
    while(this->m_str[this->m_index]>='0'&&this->m_str[this->m_index]<='9'){
        m_index++;
    }
    if(this->m_str[this->m_index]!='.'){ //如果最后不是点，则为整数 直接转换
        int i = std::atoi(this->m_str.c_str()+pos);  //c_str()返回字符串首地址指针，+pos定位到该整数位置
        return Json(i);
    }
    m_index++;
    if(this->m_str[this->m_index]<'0'||this->m_str[this->m_index]>'9'){
        throw logic_error("parse number error");
    }
    while(this->m_str[this->m_index]>='0'&&this->m_str[this->m_index]<='9'){
        m_index++;
    }
    double f = std::strtod(this->m_str.c_str()+pos,NULL);
    return Json(f);
}

string Parser::parse_string() {
    string out;
    while(true){
        char ch = this->m_str[this->m_index++]; //保留空格等
        if(ch=='"'){
            break;
        }
        if(ch=='\\'){
            ch = this->m_str[this->m_index++];
            switch (ch) {
                case '\n':
                    out+='\n';
                    break;
                case '\r':
                    out +='\r';
                    break;
                case '\t':
                    out+='\t';
                    break;
                case '\b':
                    out += '\b';
                    break;
                case '\f':
                    out+='\f';
                    break;
                case '"':
                    out+="\\\"";
                    break;
                case '\\':
                    out+="\\\\";
                    break;
                case 'u':
                    out+="\\u";//unicode码
                    for(int i = 0;i<4;i++){
                        out+=this->m_str[this->m_index++];
                    }
                    break;
                default:
                    break;
            }
        } else{
            out+=ch;
        }
    }
    return out;
}

Json Parser::parse_array() {
    Json arr(Json::json_array);
    char ch = get_next_token();
    if(ch==']'){
        return arr;
    }
    this->m_index--;
    while(true){

        arr.append(this->parse());
        ch = get_next_token();  //因为ch每次get一个token 之后会++ 所以有时需要往后退一格 进行--操作
        if(ch==']'){
            break;
        }
        if(ch!=','){
            throw logic_error("parse array error");
        }
    }
    return arr;
}

Json Parser::parse_object() {
    Json obj(Json::json_object);
    char ch  = get_next_token(); //拿到对象的第一个字符
    if(ch=='}'){  //如果是},则解析对象结束
        return obj;
    }
    this->m_index--;  //getnexttoken 把 this->mindex往前进了一步，所以要--退回来
    while(true){
        ch = get_next_token();  //拿到第一个字符
        if(ch!='"'){  //object为 pair<string,Json> 的键值对构成，所以key必须是string.
            throw logic_error("parse object error");
        }
        string key = parse_string();  //解析key为string
        ch = get_next_token();   //拿到冒号准备解析value
        if(ch!=':'){
            throw logic_error("parse object error");
        }
        obj[key] = this->parse();  //构造pair 递归调用parse 解析json的value
        ch = get_next_token();  //拿到一个词 因为此pair解析完成 后面只能是 } 或者 ，   如果是}则结束，如果是逗号，则继续解析下一个pair;
        if(ch=='}'){
            break;
        }
        if(ch!=','){
            throw logic_error("parse object error");
        }
    }
    return obj;
}

