#include <iostream>
#include <cstring>
#include <unistd.h>
#include <string.h>
#include <limits>
#include <signal.h>

const int ALIGN_R = 7;

void write_h(uint8_t b) {
    char c = (b < 10) ? char(b + '0') : char(b - 10 + 'A');
    ssize_t tmp = write(STDERR_FILENO, &c, 1);
    if (tmp == -1) {
        _exit(errno);
    }
}

void write_b(uint8_t b) {
    write_h(b / 16);
    write_h(b % 16);
}

void write_s(char const *str) {
    ssize_t cur = 0;
    ssize_t len = static_cast<ssize_t>(strlen(str));
    ssize_t tmp;
    while (cur < len) {
        tmp = write(STDERR_FILENO, str + cur, len - cur);
        if (tmp == -1) {
            _exit(errno);
        }
        cur += tmp;
    }
}

void write_r(char const *reg_s, uint64_t reg_v) {
    write_s(reg_s);
    write_s(": ");
    for (int i = 0; i < ALIGN_R - strlen(reg_s); ++i) {
        write_s(" ");
    }
    for (int i = 7; i >= 0; --i) {
        write_b(0xFF & (reg_v >> (8 * i)));
    }
    write_s("\n");
}   

void sigsegvHandler(int num, siginfo_t *siginfo, void *context)
{
    if (siginfo->si_signo == SIGSEGV)
    {
        int ret;
        write_s("Aborted: "); 
        write_s(strsignal(num));
        write_s("\n");

        ret = siginfo->si_code;
        if (ret == SEGV_MAPERR)
        {
            write_s("Reason: nothing is mapped to address\n");
        }
        else if (ret == SEGV_ACCERR)
        {
            write_s("Reason: access error\n");
        }
        else
        {
            write_s("Reason: something bad happend\n");
        }

        write_s("Registers dump: \n");
        
        struct ucontext_t *ucontext = static_cast<ucontext_t*>(context);
        write_r("R8", ucontext->uc_mcontext.gregs[REG_R8]);
        write_r("R9", ucontext->uc_mcontext.gregs[REG_R9]);
        write_r("R10", ucontext->uc_mcontext.gregs[REG_R10]);
        write_r("R11", ucontext->uc_mcontext.gregs[REG_R11]);
        write_r("R12", ucontext->uc_mcontext.gregs[REG_R12]);
        write_r("R13", ucontext->uc_mcontext.gregs[REG_R13]);
        write_r("R14", ucontext->uc_mcontext.gregs[REG_R14]);
        write_r("R15", ucontext->uc_mcontext.gregs[REG_R15]);
        write_r("RDI", ucontext->uc_mcontext.gregs[REG_RDI]);
        write_r("RSI", ucontext->uc_mcontext.gregs[REG_RSI]);
        write_r("RBP", ucontext->uc_mcontext.gregs[REG_RBP]);
        write_r("RBX", ucontext->uc_mcontext.gregs[REG_RBX]);
        write_r("RDX", ucontext->uc_mcontext.gregs[REG_RDX]);
        write_r("RAX", ucontext->uc_mcontext.gregs[REG_RAX]);
        write_r("RCX", ucontext->uc_mcontext.gregs[REG_RCX]);
        write_r("RSP", ucontext->uc_mcontext.gregs[REG_RSP]);
        write_r("RIP", ucontext->uc_mcontext.gregs[REG_RIP]);
        write_r("EFL", ucontext->uc_mcontext.gregs[REG_EFL]);
        write_r("CSGSFS", ucontext->uc_mcontext.gregs[REG_CSGSFS]);
        write_r("ERR", ucontext->uc_mcontext.gregs[REG_ERR]);
        write_r("TRAPNO", ucontext->uc_mcontext.gregs[REG_TRAPNO]);
        write_r("OLDMASK", ucontext->uc_mcontext.gregs[REG_OLDMASK]);
        write_r("CR2", ucontext->uc_mcontext.gregs[REG_CR2]);
        
        write_s("Memory dump: \n");

        int pipe_fd[2];
        ret = pipe(pipe_fd);
        if (ret == -1) {
            write_s("Can't pipe\n");
            _exit(45);
        }
        for (int i = -8; i < 8; i++) {
            char *t = (char*) (siginfo->si_addr) + i;
            ret = write(pipe_fd[1], t, 1);
            
            if (i == 0) {
                write_s("[");
            } else {
                write_s(" ");
            }
            
            if (ret == -1) {
                write_s("??");
            } else {
                uint8_t value;
                ret = read(pipe_fd[0], &value, 1);
                if (ret == -1) {
                    write_s("??");
                } else {
                    write_b(value);
                }
            }
            
            if (i == 0) {
                write_s("] ");
            } else {
                write_s("  ");
            }

            if ((i & 15) == 15) {
                write_s("\n");
            }
        }
        write_s("\n"); 
    }
    _exit(46);
}

int main(int argc, char *argv[], char *envp[])
{
    struct sigaction action {};
    int ret;
    action.sa_flags = SA_SIGINFO | SA_NODEFER;
    ret = sigemptyset(&action.sa_mask);
    if (ret == -1) {
        fprintf(stderr, "sigemptyset: %s\n", strerror(errno));
        return -1;
    }

    action.sa_sigaction = sigsegvHandler;
    ret = sigaction(SIGSEGV, &action, nullptr);
    if (ret == -1) {
        fprintf(stderr, "sigaction: %s\n", strerror(errno));
        return -1;
    }
    char *test;
    //case 1:
        // test = nullptr;
        // *test = 1;
    //case 2:
        // test = (char *)"data";
        // *(--test) = 'A';
    //case 3:
        test = (char *)"data";
        test[5] = '1';
    return 0;
}
