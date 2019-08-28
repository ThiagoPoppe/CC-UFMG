#include <iostream>

int main(int argc, const char** argv) {
    int H, M, T;
    std::cin >> H >> M >> T;
    
    M += T;
    H += M / 60;

    std::cout << H % 24 << ":" << M % 60 << std::endl;
    return 0;
}