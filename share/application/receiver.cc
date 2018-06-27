#include <iostream> 

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>

#define sys_err(message) std::cerr << message << std::endl;\
	std::cerr << "line " << __LINE__ << ": " << strerror(errno) << std::endl;\
	return -1;

#define debug(variable) std::cout << variable << std::endl;
#define DEBUG_

double computeRate(struct timespec *start, struct timespec *end, int n) {
	const double nano = 1e9;
	return n * 4 / (end->tv_nsec/nano + end->tv_sec - start->tv_sec - start->tv_nsec/nano);
}

int receive() {
	int listenfd, connfd;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		sys_err("establish listenfd failed!");
	}
#ifdef DEBUG_
	//debug(listenfd);
#endif
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(2019);
	
	if (bind(listenfd, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		sys_err("bind server address failed!");

	}

	if (listen (listenfd, 5) < 0) {
		sys_err("listen on port 2019 failed!");
	}

	connfd = accept(listenfd, NULL, 0);
	if (connfd < 0) {
		sys_err("accept client failed!");
	}
	int fd;
	char buff[4096];
	int n = 0;
	bzero(buff, sizeof(buff));
	if ((n = read(connfd, buff, sizeof(buff))) < 0) {
		sys_err("read filename from remote failed!");
	}
	else {
		char *p = strchr(buff, '\n');
		*p = '\0';
		//int fd;
		if ((fd = open(buff, O_CREAT | O_RDWR)) < 0) {
			sys_err("create new file failed!");
		}
		++p;
		if (write(fd, p, n - (p - buff)) < 0) {
			sys_err("write to file failed!");
		}
	}
	
	//bzero(buff, sizeof(buff));
	int i = 1;
	struct timespec start, end;
	if (clock_gettime(CLOCK_REALTIME, &start) < 0) {
		sys_err("clock_get start time failed!");
	}
	while ((n = read(connfd, buff, sizeof(buff))) > 0) {
		if(write(fd, buff, n) < 0) {
			sys_err("write to file failed!");
		}
		//bzero(buff, strlen(buff));
		++i;
	}
	if (clock_gettime(CLOCK_REALTIME, &end) < 0) {
		sys_err("clock_get end time failed!");
	}
	std::cout << computeRate(&start, &end, i) << " k/s" << std::endl;
	//std::cout << "write to file finished!" << std::endl;
	return 0;
}

int main() {
	receive();
	return 0;
}
