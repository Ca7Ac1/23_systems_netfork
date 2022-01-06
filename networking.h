#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#ifndef NETWORKING_H
#define NETWORKING_H

#define SERVER_IP NULL
#define CLIENT_IP "149.89.150.119"
#define PORT "9001"

#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000

int server_setup(char *addr, char *port);
int server_fork(int server_socket, int *connection);
int client(char *addr, char *port);

#endif
