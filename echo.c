#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define PORT 54322
#define BACKLOG 5

/*
 * This function sets up a socket listening on local port.
 *
 * port: port number to listen on.
 * :return: socket file descriptor.
 */
int setup_sock(int port) {

    int listen_fd;
    struct sockaddr_in serv_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(listen_fd, BACKLOG);

    return listen_fd;
}


void echo_request(int conn_fd) {
    int n;
    time_t ticks;
    char sendBuff[BUFFER_SIZE];
    char recvBuff[BUFFER_SIZE];

    memset(sendBuff, 0, sizeof(sendBuff));
    memset(recvBuff, 0, sizeof(recvBuff));

    while ((n = (int) recv(conn_fd, recvBuff, sizeof(recvBuff), 0)) > 0) {
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s: ", ctime(&ticks));

        recvBuff[n] = '\0';
        printf("received:  %s", recvBuff);
        strcat(sendBuff, recvBuff);
        send(conn_fd, sendBuff, strlen(sendBuff), 0);
    }
    printf("received 0 bytes, close.\n");
    close(conn_fd);
}


int main(int argc, char *argv[]) {
    int listen_fd = 0, conn_fd = 0;
    socklen_t cli_len;
    struct sockaddr_in cli_addr;

    printf("start server...\n");
    memset(&cli_addr, '0', sizeof(cli_addr));

    listen_fd = setup_sock(PORT);
    printf("listening on 0.0.0.0 %d...\n", PORT);

    cli_len = sizeof(cli_addr);
    int i = 0;
    while (i < 100) {
        conn_fd = accept(listen_fd, (struct sockaddr *) &cli_addr, &cli_len);
        printf("client ip: %s, port: %d\n",
               inet_ntoa(cli_addr.sin_addr),
               ntohs(cli_addr.sin_port));

        echo_request(conn_fd);

        i++;
    }
}