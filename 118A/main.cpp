#include <iostream>
#include <string>
#include <cctype>


std::string check_char(char lower_chr)
{
    const char vowels[] { 'u', 'e', 'o', 'a', 'i', 'y' }; 
    for (const char &vowel: vowels)
    {
        if (lower_chr == vowel)
        {
            return std::string {""};
        }
    }

    return std::string {'.', lower_chr};
}


int main (){

    std::string string_input;
    std::cin >> string_input;

    std::string new_string;

    for (const char &chr: string_input)
    {
        char lower_case = std::tolower(chr);
        new_string += check_char(lower_case);
    }

    std::cout << new_string << '\n';
    return 0;
}