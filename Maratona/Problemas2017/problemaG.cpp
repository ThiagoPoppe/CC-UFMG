#include <iostream>
#include <string>

int main(int argc, const char** argv) {
    std::string s;
    std::cin >> s;

    for(unsigned int i = 0; i < s.size(); i++) {
        int j = i;
        int n = 0;
        while (s[i] == s[j++]) n++;

        std::cout << s[i] << n;
        i += n - 1;
    }

    std::cout << std::endl;

    return 0;
}