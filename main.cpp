#include <iostream>
#include <string>
#include <vector>
#include <cpr/cpr.h>

int main() {

    std::string argument = "";
    std::string value = "";
    std::vector<cpr::Pair> opt;
    cpr::Response res;
    do
    {
        std::cout << "Enter the argument and its value for the request";
        std::cout << "or get/post to execute the request itself:" << std::endl;
        std::cin >> argument;

        if (argument != "get" && argument != "post")
        {
            std::cin >> value;
            opt.push_back(cpr::Pair(argument,value));
        }
    } while (argument != "get" && argument != "post");

    if (argument == "get")
    {
        std::string url = "http://httpbin.org/get?";
        for (auto it = opt.begin();it != opt.end();++it)
        {
            if(it != opt.begin()) url += '&';
            url += it->key + '=' + it->value;
        }

        res = cpr::Get(cpr::Url(url));

        std::cout << res.text << std::endl;
    }
    else if (argument == "post")
    {
        res = cpr::Post(cpr::Url("http://httpbin.org/post"),
                        cpr::Payload(opt.begin(),opt.end()));
        std::cout << res.text << std::endl;
    }
    return 0;
}
