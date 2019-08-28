#include <iostream>

int f(int n) {
    if (n == 0) {
        return 0;
    }
    
    else if (n == 1 || n == 2) {
        return 1;
    }
    
    else {
        return f(n-1) + f(n-2) - f(n-3);
    }
}

int main(int argc, const char** argv) {
    int t, v;
    std::cin >> t;

    for (int i = 0; i < t; i++) {
        std::cin >> v;
        std::cout << f(v) << std::endl;
    }

    return 0;
}