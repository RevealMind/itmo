#include<iostream>
#include<dlfcn.h>

#include"binpow.hpp"
#include"fact.hpp"

int main(int argc, char *argv[], char *envp[]) {
    const char * dynamic_linked_lib = "libgcd.so";
    void *gcd_lib = dlopen(dynamic_linked_lib, RTLD_LAZY);

    if (gcd_lib == nullptr) {
        std::cerr << "Could not open " << dynamic_linked_lib << "\n";
        exit(EXIT_FAILURE);
    }

    auto ptr_gcd = (int(*)(int, int))(dlsym(gcd_lib, "gcd"));
    
    if (ptr_gcd == nullptr) {
        std::cerr << "Could not load gcd from " << dynamic_linked_lib << "\n";
        dlclose(gcd_lib);
        exit(EXIT_FAILURE);
    }
    std::cout << "Enter 2 numbers: ";
    int a, b;
    std::cin >> a >> b;

    std::cout << a << " ^ " << b << " == " << binpow(a, b) << "\n\n";

    std::cout << a << "! == " << fact(a) << "\n";
    std::cout << b << "! == " << fact(b) << "\n\n";

    

    std::cout << "gcd(" << a << ", " << b << ") == " << ptr_gcd(a, b) << std::endl;
    dlclose(gcd_lib);
    return 0;
}