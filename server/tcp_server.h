/*	Author: Valentin Svirskyi
	E-mail: barabashka25219@icloud.com
	Date: 10.12.2021
*/
#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#define PORT 5555			// server port
#define MESSAGE_SIZE 1024	// size of sent/received message

/* Show an error and exit from program */
void raise_error_and_exit(char *function_name);

/* Build TCP server and run. it returns a socket of server */
int build_server_and_run();

/* Build welcome message and send it */
void *build_answer_and_send(int client_sock);

/* Receive answer from client and output it to log */
void *receive_answer_from_client(int client_sock);

#endif
