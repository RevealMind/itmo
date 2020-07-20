#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <alloca.h>
#include "utils.cpp"


int const BUFF_SIZE = 2048
;

/*
 * first arg - name of server to connect
 * second arg - name of file
 */
int main(int argc, char **argv) {

    if (argc != 3) {
        std::cerr << "Incorrect number of args\n";
        exit(EXIT_FAILURE);
    }

    char *file = argv[2];
    struct sockaddr_un server_addr;
    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        show_error("socket");
    }

    std::cout << "Connection..." << std::endl;

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, argv[1]);
    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        show_error("connect");
    }
    std::cout << "Connected to server!" << std::endl;

    write_str(sock, file);

    char io_buffer[BUFF_SIZE];
    struct iovec io;
    struct msghdr msg;
    struct cmsghdr *cmsg;
    int fd;

    io.iov_base = io_buffer;
    io.iov_len = BUFF_SIZE;

    msg.msg_name = nullptr;
    msg.msg_namelen = 0;
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;

    cmsg = (cmsghdr *) alloca(sizeof(struct cmsghdr) + sizeof(fd));
    cmsg->cmsg_len = sizeof(struct cmsghdr) + sizeof(fd);
    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg->cmsg_len;

    if (recvmsg(sock, &msg, 0) < 0) {
        show_error("recvmsg");
    }
    memcpy(&fd, CMSG_DATA(cmsg), sizeof(fd));
    std::cout << "Input your text.\n"
                 "After that it will be reverse and all letters will be replaced and input in file\n"
                 "To finish work send '!exit'\n"
                 "To finish work of client and server send !stop" << std::endl;
    bool next = true;
    while (next) {
        char requeset[BUFF_SIZE];
        scanf("%s", requeset);
        if (strcmp(requeset, "!exit") == 0 || 
            strcmp(requeset, "!stop") == 0) {
            next = false;
        }
        write_str(fd, requeset);
        if (!next){
            std::cout << "Success!" << std::endl;
        }
    }
    remove(file);
    std::cout << "Closed and removed." << std::endl;
    close(sock);
    return 0;
}
