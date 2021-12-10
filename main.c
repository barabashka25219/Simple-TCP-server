#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server/tcp_server.h"

int main(void) {

	int serv_sock;
	int client_sock;
	struct sockaddr_in client_addr;
	int sin_size = sizeof(struct sockaddr_in);

	// Строим и запускаем сервер
	serv_sock = build_server_and_run();

	while(1) {

		// Принимаем новое соединение
		client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &sin_size);
		fprintf(stdout, "[LOG] Got connection from %s.\n", inet_ntoa(client_addr.sin_addr));

		// Строим и отправляем сообщение клиенту
		build_answer_and_send(client_sock);

		// Принимаем сообщение от клиента 
		receive_answer_from_client(client_sock);

		// Закрываем соединение
		close(client_sock);
	}
}

