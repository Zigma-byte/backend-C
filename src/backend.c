#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 3);

    printf("C server running on port %d\n", PORT);

    while (1) {
        int client = accept(server_fd, NULL, NULL);
        char buffer[1024];
        read(client, buffer, 1024);

        if (strncmp(buffer, "GET /click", 10) == 0) {
            const char *response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Access-Control-Allow-Origin: *\r\n"
                "Connection: close\r\n\r\n"
                "Button was clicked!";
            write(client, response, strlen(response));
        }

        close(client);
    }
}
