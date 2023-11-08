#include <iostream>
#include "json.h"
#include "Parser.h"
using namespace Ty::json;

int main() {
    Json v1;
    Json v2 = true;
    Json vi = true;
    bool flag =  v2==vi;
    cout << flag <<endl;
    Json v3 = 123;
    Json v4 = 1.23;
    Json v5 = "hello,world";

    bool b = v2;  //重载类型转换运算符  使用类似 bool b = v2这种时 将v1进行类型转换bool(v2),我们重载这个运算符返回m_value中的bool值。
    int i = v3;
    double f = v4;
    const string & s = v5;

    std::cout << b << " " << i << " " << f << " " << s <<std::endl;


    Json arr;
    arr[0] = true;
    arr[1] = 123;
    arr.append(1.23);
    arr.append("hello world");

    bool c = arr[0];
    int d = arr[1];
    double e = arr[2];
    const string & g = arr[3];
    cout << c <<" " <<d << " " << e <<" " << g <<endl;

    cout << arr.str() <<endl;

    Json obj;
    obj["bool"] = true;
    obj["int"] = 123;
    obj["double"] = 1.23;
    obj["string"] = "hello world";
    cout << obj.str() <<endl;

    Json obj1;
    obj1["bool"] = true;
    obj1["int"] = 123;
    obj1["double"] = 1.23;
    obj1["string"] = "hello world";
    cout << obj1.str() <<endl;
    string  flag2 = obj==obj1?"True":"False";
    cout << flag2 <<endl;



    Json new_arr;
    new_arr[0] = true;
    new_arr[1] = 123;
    new_arr[2] = 1.23;
    new_arr[3] = "hello world";
    std::cout << new_arr.str() << std::endl;
    //->str()把json格式化输出
    for(auto it = new_arr.begin();it!=new_arr.end();it++){
        cout << it->str() <<endl;
    }
    string  flag1 = arr==new_arr?"True":"False";
    cout << flag1 <<endl;


    bool flag3 = new_arr.has(0);
    cout << flag3 <<endl;

    flag3 = obj1.has("bool");
    cout << flag3 <<endl;

    new_arr.remove(1);
    cout << new_arr.str() <<endl;

    obj1.remove("bool");
    cout << obj1.str() <<endl;
    obj1.clear();
    cout << obj.str() <<endl;

    //动态释放内存时，需要从根节点开始clear,遇到object和array时，会进行递归释放。
    //Parser测试
    const string & str = "false";
    Json v;
    v.parse(str);
    cout << v.str() <<endl;

    const string & str1 = "-5.2";
    Json v11;
    v11.parse(str1);
    cout << v11.str() <<endl;

//    const string & str2 = "\"hello world\"";
//    Json v12;
//    v12.parse(str2);
//    cout << v12.str() <<endl;
//
    const string & str3 = "[\"hello\",1,5,6,7,true,false,null,[1,2,3,4,5]]";
//    //const string & str3 = "[true,false]";
    Json v13;
    v13.parse(str3);
    cout << v13.str() <<endl;

    //const string & str4 = "{\"a\":1,\"b\":2,\"c\":3,\"d\":true,\"e\":true,\"f\":null}";
    //const string  & str4 = "{\"code\":0,\"message\":\"成功\",\"request_id\":\"35d045dc7f064f08a1a84a9b1bcaf947\",\"ts\":1679402969074,\"data\":{\"panel\":[{\"href\":\"https://game.bilibili.com/blhx/\",\"title\":\"碧蓝航线\",\"poster\":\"//i0.hdslb.com/bfs/game/f2726119665b7434e8006569435e5662b6445c36.png\"}";
    const string  & str4 = "{\"code\":0,\"message\":\"成功\",\"request_id\":\"35d045dc7f064f08a1a84a9b1bcaf947\",\"ts\":1679402969074,\"data\":{\"panel\":[{\"href\":\"https://game.bilibili.com/blhx/\",\"title\":\"碧蓝航线\",\"poster\":\"//i0.hdslb.com/bfs/game/f2726119665b7434e8006569435e5662b6445c36.png\"}]}}";
    Json v14;
    v14.parse(str4);
    cout << v14.str() <<endl;

    Json arr1;
    arr1[0] = true;
    arr1[1] = 123;
    arr1[2] = "hello world";

    Json obj4;
    obj4["bool"] = false;
    obj4["int"] = 123;
    obj4["double"] = 1.23;
    obj4["arr"] = arr1;
    cout << obj4.str() <<endl;
    arr1.clear();
    obj4.clear();



    return 0;
}
