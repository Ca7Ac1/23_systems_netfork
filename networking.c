#include "networking.h"


int server_setup(char *addr, char *port)
{
    struct addrinfo *results;

    struct addrinfo *hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    getaddrinfo(addr, port, hints, &results);

    int server_socket = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    if (server_socket == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }

    if (bind(server_socket, results->ai_addr, results->ai_addrlen) == -1)
    {
        printf("%s\n", strerror(errno));
        return -1;
    }

    listen(server_socket, 10);

    free(hints);
    freeaddrinfo(results);

    return server_socket;
}

int server_fork(int server_socket, int *connection)
{
    struct sockaddr_storage address;
    socklen_t sock_size = sizeof(address);
    *connection = accept(server_socket, (struct sockaddr *) &address, &sock_size);

    int c = fork();

    return c;
}

int client(char *addr, char *port)
{
    struct addrinfo *results;
    
    struct addrinfo *hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_flags = AI_PASSIVE;

    getaddrinfo(addr, port, hints, &results);

    int connection = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    connect(connection, results->ai_addr, results->ai_addrlen);

    return connection;
}
