#include <iostream>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.cpp"


int const BUFF_SIZE = 2048;

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "Incorrect number of args\n";
        exit(EXIT_FAILURE);
    }

    char *server_name = argv[1];
    unlink(server_name);

    int sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
        show_error("socket");
    }

    int client_sockfd;
    struct sockaddr_un server_addr;
    struct sockaddr_un client_addr;
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, server_name);
    if (bind(sock, (struct sockaddr *) &server_addr, sizeof(server_addr))) {
        show_error("bind");
    }

    listen(sock, 5);
    std::cout << "Connection..." << std::endl;

    while (true) {
        ssize_t read_size;
        char buffer[BUFF_SIZE];
        char io_buff[BUFF_SIZE];
        int fd;

        socklen_t client_len = sizeof(client_addr);
        client_sockfd = accept(sock, (struct sockaddr *) &client_addr, &client_len);

        if (client_sockfd < 0) {
            show_error("accept");
        }

        if ((read_size = read(client_sockfd, buffer, BUFF_SIZE)) < 0) {
            show_error("read");
        }

        buffer[read_size] = '\0';
        strncpy(io_buff, buffer, static_cast<size_t>(read_size + 1));

        if (mkfifo(io_buff, 0777)) {
            show_error("mkfifo");
        }

        if ((fd = open(io_buff, O_RDWR)) <= 0) {
            remove(io_buff);
            show_error("open");
        }

        std::cout << io_buff << " opened." << std::endl;

        struct iovec iovec_;
        struct msghdr msg;
        struct cmsghdr *cmsg;

        iovec_.iov_base = io_buff;
        iovec_.iov_len = strlen(io_buff) + 1;

        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = &iovec_;
        msg.msg_iovlen = 1;

        cmsg = (struct cmsghdr *) alloca(sizeof(struct cmsghdr) + sizeof(fd));
        cmsg->cmsg_len = sizeof(struct cmsghdr) + sizeof(fd);
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;

        memcpy(CMSG_DATA(cmsg), &fd, sizeof(fd));

        msg.msg_control = cmsg;
        msg.msg_controllen = cmsg->cmsg_len;

        if (sendmsg(client_sockfd, &msg, 0) != static_cast<ssize_t >(iovec_.iov_len)) {
            remove(io_buff);
            show_error("sendmsg");
        }

        close(client_sockfd);
        memcpy(&fd, CMSG_DATA(cmsg), sizeof(fd));

        bool next = true;
        while (true) {
            char buff[BUFF_SIZE];
            if ((read_size = read(fd, buff, BUFF_SIZE - 1)) < 0) {
                show_error("read");
            }

            buff[read_size] = '\0';
            if (strcmp("!exit", buff) == 0) {
                break;
            }

            if (strcmp("!stop", buff) == 0) {
                next = false;
                break;
            }
            std::cout << "---------------------------------------------------------" << std::endl;
            std::cout << "Message: " << buff << std::endl << std::endl;
            char response[read_size + 1];
            response[read_size] = '\0';
            for (int i = 0; i < read_size; i++) {
                response[i] = buff[read_size - 1 - i];
            }
            std::cout << "Answer: " << response << std::endl;
            std::cout << "---------------------------------------------------------" << std::endl;

        }
        std::cout << "Close..." << std::endl;
        std::cout << "Good Bye!" << std::endl;
        close(fd);
        if (!next) {
            break;
        }
    }
    close(sock);
    return 0;
}