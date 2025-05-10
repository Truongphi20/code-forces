#include <iostream>
#include <string>

void checkHello(std::string hello_string)
{
    const std::string hello{ "hello" };

    int marker{0};
    for (char chr: hello_string)
    {
        if (chr == hello[marker])
        {
            marker += 1;
        }
    }

    if (marker == hello.size()){
        std::cout << "YES" << '\n';
    }else{
        std::cout << "NO" << '\n';
    }
}



int main()
{
    std::string hello_string;
    std::cin >> hello_string;

    checkHello(hello_string);

    return 0;
}