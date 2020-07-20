#include<iostream>
#include <string.h>
#include <sys/mman.h>
#include<vector>
#include<sstream>
#include<iterator>

using std::vector;
using std::string;

unsigned char func[] = {
        0x55,                                     // push   %rbp
        0x48, 0x89, 0xe5,                         // mov    %rsp,%rbp
        0xc7, 0x45, 0xf8, 0x01, 0x00, 0x00, 0x00, // movl   $0x1,-0x8(%rbp)
        0xc7, 0x45, 0xfc, 0x01, 0x00, 0x00, 0x00, // movl   $0x1,-0x4(%rbp)
        0x8b, 0x55, 0xf8,                         // mov    -0x8(%rbp),%edx
        0x8b, 0x45, 0xfc,                         // mov    -0x4(%rbp),%eax
        0x5d,                                     // pop    %rbp
        0x01, 0xd0,                               // add    %edx,%eax
        0xc3                                      // retq   
};   

void show_usage() {
    std::cout << "Usage: command\n\n" 
                 "Command list: \n" 
                 "\texec [arg1 [arg2]] - executes function with <arg1> and <arg2>. (Function is sum of two nubmers (by default arg1 = arg2 = 1))\n"
                 "\texit               - close JIT\n"
                 "\thelp               - show this message\n" << std::flush;

}   

void show_error(std::string const& error_message) {
    std::cerr << "ERROR: " + error_message + ". (" + strerror(errno) + ")\n";
}

class JIT_compiler {
public:
    JIT_compiler(size_t pageSize = 8192) : lenght(pageSize), prot(PROT_READ | PROT_WRITE) {
        mem = mmap(nullptr, sizeof(func), prot, MAP_PRIVATE | MAP_ANON, -1, 0);
        if (mem == MAP_FAILED) {
            show_error("Failed when allocate memory");
            exit(EXIT_FAILURE);
        }
        memcpy(mem, func, sizeof(func));
    }

    ~JIT_compiler() {
        if (munmap(mem, lenght) == -1) {
            show_error("Failed when deallocate memory");
            exit(EXIT_FAILURE);
        }
    }

    void patch(size_t num_arg, int new_arg) {
        set_prot(PROT_WRITE | PROT_READ);
        size_t ind = positions[num_arg];
        ((unsigned char*) mem)[ind + 3] = static_cast<unsigned char>((new_arg >> 24) & 0xFF);
        ((unsigned char*) mem)[ind + 2] = static_cast<unsigned char>((new_arg >> 16) & 0xFF);
        ((unsigned char*) mem)[ind + 1] = static_cast<unsigned char>((new_arg >> 8) & 0xFF);
        ((unsigned char*) mem)[ind    ] = static_cast<unsigned char>(new_arg & 0xFF);
    }

    int exec() {
        set_prot(PROT_READ | PROT_EXEC);
        return ((int (*)()) mem)();
    }

private:
    void set_prot(int new_prot) {
        if (prot != new_prot) {
            if (mprotect(mem, lenght, new_prot) == -1) {
                show_error("Failed when set prot");
                exit(EXIT_FAILURE);
            }
            prot = new_prot;
        }
    }

    void * mem;
    size_t lenght;
    int prot;
    size_t positions[2] = {7, 14};
};


vector<string> parseCommand(string const & str) {
    std::istringstream stream(str);
    vector<string> out   {std::istream_iterator<string>(stream),
                          std::istream_iterator<string>()};
    return out;
}

bool parseInt(string const &str, int& out) {
    std::istringstream stream(str);
    return stream >> out ? true : false;
}

int main() {
    std::string in;
    JIT_compiler compiler = JIT_compiler();
    show_usage();
    while (std::getline(std::cin, in)) {
        vector<string> command = parseCommand(in);
        if (command.empty()) {
            continue;
        }
        if (command.size() > 3) {
            show_error("Not vailid ammount of arguments");
            show_usage();
            continue;
        }
        if (command[0] == "exit") {
            std::cout << "Good bye!" << std::endl;
            exit(EXIT_SUCCESS);
        } else if (command[0] == "help") {
            show_usage();
        } else if (command[0] == "exec") {
            int arg1 = 1, arg2 = 1;
            switch (command.size()) {                
                case 3:
                    arg2;
                    if (!parseInt(command[2], arg2)) {
                        show_error("Not valid argument: " + command[2]);
                        continue;
                    }
                    compiler.patch(1, arg2);
                case 2:
                    arg1;
                    if (!parseInt(command[1], arg1)) {
                        show_error("Not valid argument: " + command[1]);
                        continue;
                    }
                    compiler.patch(0, arg1);
                    break;
                default :
                    compiler.patch(0, arg1);
                    compiler.patch(1, arg2);
            }            
            std::cout << "Function out: " << arg1 <<  " + " <<  arg2 <<  " = " << compiler.exec() << std::endl;
        } else {
            show_error("Unkown command");
            continue;
        }
    }
    return 0;
}