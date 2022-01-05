#include <signal.h>

#include "pipe_networking.h"

void process(char *);
void quick(char *, int, int);
int partition(char *, int, int);
void swap(char *, int, int);

static void sighandler(int signo)
{
	if (signo == SIGINT)
	{
		exit(0);
	}
}

int main() {
	signal(SIGINT, sighandler);

    int server = server_setup(SERVER_IP, SERVER_PORT);

    if (server == -1)
    {
        return -1;
    }

    printf("[%d] : [Server setup]", getpid());

    while (1)
	{
        printf("[%d] : [Main server accepting new client]", getpid());

        int connection;
		int c = server_fork(server, &connection);

		if (connection == -1 || c == -1)
		{
            printf("%s\n", strerror(errno));
			return -1;
		}

        if (c == 0)
        {
            printf("[%d] : [Subserver connected]", getpid());

            char input[BUFFER_SIZE];
            while (read(connection, input, BUFFER_SIZE) > 0)
            {
                process(input);

                if (write(connection, input, BUFFER_SIZE) == -1)
                {
                    printf("%s\n", strerror(errno));
                }
            }

            printf("Client exited\n");
            exit(0);
        }

		close(from_client);
		close(to_client);
	}

	return 0;
}

void process(char *input)
{
	while (strlen(input) > 1 && input[strlen(input) - 1] == '\n')
	{
		input[strlen(input) - 1] = '\0';
	}

	quick(input, 0, strlen(input));
}

void quick(char *input, int l, int r)
{
	if (l >= r)
	{
		return;
	}

	int ind = partition(input, l, r);
	quick(input, l, ind);
	quick(input, ind + 1, r);
}

int partition(char *input, int l, int r)
{
	int index = l;
	for (int i = l; i < r - 1; i++)
	{
		if (input[i] < input[r - 1])
		{
			swap(input, i, index);
			index++;
		}
	}

	swap(input, index, r - 1);
	return index;
}

void swap(char *input, int a, int b)
{
	char temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}
