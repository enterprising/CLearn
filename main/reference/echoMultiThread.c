/*************************************************************************
  > File Name: server.c
  > Author: VOID_133
  > 多线程版
  > A very simple tcp echo server illustrate use of socket
  > Ver1 only accept single connection, no multiple connection allowed
  > Mail: ################### 
  > Created Time: Wed 21 Dec 2016 04:03:25 PM HKT
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/errno.h>

#define MAX_BUF_SIZE 1000

typedef struct thread_args {
    int clifd;
} ThreadArgs;


void usage(char *proc_name) {
    printf("%s [port]\n", proc_name);
    exit(1);
}

// Handle connections per thread
void *handle_conn(void *args) {
    ThreadArgs *targs = args;
    //printf("fd = %d\n", targs->clifd);
    //printf("args = %x\n", args);
    int ret = 0;
    char buf[MAX_BUF_SIZE];
    memset(buf, 0, sizeof(buf));
    while (ret = read(targs->clifd, buf, (size_t) MAX_BUF_SIZE) && ret != EOF) {
        //printf("Client message: %s\n", buf);
        ret = write(targs->clifd, buf, sizeof(char) * (strlen(buf) + 1));
        if (ret < 0) {
            perror("write()");
            break;
        }
        memset(buf, 0, sizeof(buf));
    }
    close(targs->clifd);
    free(args);
    return NULL;
}

int main(int argc, char **argv) {
    int sockfd, clifd;

    //sockaddr_in is used to describe internet(IPV4) socket address
    struct sockaddr_in server_in_addr;
    int ret = 0;
    int port = 8080;
    ThreadArgs *targs = NULL;
    pid_t child_pid;

    if (argv[1] == NULL) {
        usage(argv[0]);
    }
    port = atoi(argv[1]);


    //create the socket flide
    //AF_INET is the address family for internet, SOCK_STREAM means TCP connections
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket()");
        exit(-1);
    }
    //Set all bytes to zero
    bzero(&server_in_addr, sizeof(server_in_addr));
    server_in_addr.sin_family = AF_INET;

    //inet_aton convert string based address to binary data
    //Do not use inet_addr, for more info see man page
    ret = inet_aton("0.0.0.0", &server_in_addr.sin_addr);

    //You can also choose the code below to let socket
    //listen to all interface
    //code: server_in_addr.sin_addr.s_addr =  htonl(INADDR_ANY);

    //Convert unsigned short to on-wire data
    server_in_addr.sin_port = htons(port);
    if (ret < 0) {
        perror("inet_aton()");
        exit(-1);
    }

    //Let socket bind to the server address and port
    ret = bind(sockfd, (const struct sockaddr *) &server_in_addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
        perror("bind()");
        exit(-1);
    }

    //Listen for incoming connections
    ret = listen(sockfd, 50);
    if (ret < 0) {
        perror("listen()");
        exit(-1);
    }
    // Initialize thread_list variable
    int thread_cnt = 0;
    pthread_t *thread_list = NULL;
    while (1) {
        //accept will block until a client connect to the server
        //Use pthread_create to create thread for handling connections
        clifd = accept(sockfd, NULL, NULL);
        if (clifd < 0) {
            perror("accept()");
            exit(-1);
        }
        printf("Create thread with fd = %d\n", clifd);
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        thread_cnt++;
        targs = (ThreadArgs *) malloc(sizeof(ThreadArgs));
        targs->clifd = clifd;
        thread_list = (pthread_t *) realloc((void *) thread_list, thread_cnt * sizeof(pthread_t));
        ret = pthread_create(&thread_list[thread_cnt - 1], &attr, handle_conn, (void *) targs);
        if (ret < 0) {
            perror("pthread_create()");
            exit(-1);
        }
    }
    return 0;
}