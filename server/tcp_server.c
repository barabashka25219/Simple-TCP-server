#include "tcp_server.h"

void raise_error_and_exit(char *function_name) {

	perror(function_name);

	exit(0);

}

int build_server_and_run() {

	int server_sock;
	struct sockaddr_in serv_addr;
	int yes = 1;
	int sin_size;

	// Открыть TCP-сокет
	if((server_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		raise_error_and_exit("socket() ");

	// Установить опции сокета: 1 аргумент - сокет, 2 аргумент - опции сокета, 3 - сама опция
	// 4 - аргумент опции, 5 - размер аргумента опции
	if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		raise_error_and_exit("setsockopt() ");

	// Заполнить адресную структуру сокета сервера
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = 0;
	memset(&(serv_addr.sin_zero), 0, 8);

	// Привязать сокет к адресным данным
	if(bind(server_sock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
		raise_error_and_exit("bind() ");

	// Слушать подключения к серверу
	if(listen(server_sock, 5) == -1)
		raise_error_and_exit("listen() ");

	fprintf(stdout, "Server built and run on %hu port.\n", ntohs(serv_addr.sin_port));

	return server_sock;
}

void *build_answer_and_send(int client_sock) {

	char *answer = malloc(MESSAGE_SIZE);
	memset(answer, '\0', MESSAGE_SIZE);

	strcat(answer, "Server: Hello, Server here.\n");
	strcat(answer, "Server: Write to me anything.\n");

	if(send(client_sock, answer, strlen(answer), 0) == -1)
		perror("send() ");

	free(answer);
}

void *receive_answer_from_client(int client_sock) {

	char *answer = malloc(MESSAGE_SIZE);
	memset(answer, '\0', MESSAGE_SIZE);

	if(recv(client_sock, answer, MESSAGE_SIZE, 0) == -1)
		perror("recv() ");

	if(strlen(answer) > 0)
		fprintf(stdout, "Client: %s\n", answer);

	free(answer);
}
