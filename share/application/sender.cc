#include <iostream>
#include <fstream>

#include <netinet/in.h> //struct sockaddr_in
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define sys_err(message) std::cout << message << std::endl;return -1;

int send(const char *fileName, const char *ip) {
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2019);
	if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) < 0) {
		sys_err("assign server address failed!");
	}
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverfd < 0) {
		sys_err("initialize serverfd failed!");
	}
	
	if (connect(serverfd, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		sys_err("connect to remote failed!");
	}
	char buff[4096];
	bzero(buff, sizeof(buff));
	strncpy(buff, fileName, strlen(fileName));
	strcat(buff, "\n");

	if (write(serverfd, buff, strlen(buff)) < 0) {
		sys_err("write to server failed!");
	}

	int fd;
	if ((fd = open(fileName, O_RDONLY)) < 0) {
		sys_err("open send file failed!");
	}
	//bzero(buff, sizeof(buff));
	int n = 0;
	while ((n = read(fd, buff, sizeof(buff))) >= 0) {
		if (write(serverfd, buff, n) < 0) {
			sys_err("send to server failed!");
		}
		//std::cout << buff << std::endl;
		if (n == 0) break;
		//bzero(buff, sizeof(buff));
	}
	return 0;
}

int main() {
	send("hello.txt", "10.170.64.236");
	return 0;
}
