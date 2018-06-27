#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <memory>

#include <error.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <libgen.h>
#include <pthread.h>
#include <poll.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

#define sys_err(message) perror(message); return -1;
#define ntohll(x) ((1==htonl(1)) ? (x) : (((uint64_t)htonl((x) & 0xFFFFFFFFULL)) << 32) | htonl((uint32_t)((x) >> 32)))
#define htonll(x) ((1==ntohl(1)) ? (x) : (((uint64_t)ntohl((x) & 0xFFFFFFFFULL)) << 32) | ntohl((uint32_t)((x) >> 32)))


typedef long long ll;

static const int fregular = 1;
static const int fdirectory = 2;

static const char mip[] = "225.0.0.1";

static const int msgport = 2019;
static const int metaport = 2020;
static const int fileport = 2021;


class Meta {
public:
	std::string path;
	int type;
	ll len;
	char ipbuf[16];
	Meta(){
		//bzero(ipbuf, sizeof(ipbuf));
		memset(ipbuf, 0, sizeof(ipbuf));
	}
	bool operator==(const Meta &m) {
		return this->path == m.path
			&& this->len == m.len
			&& this->type == m.type
			//do not forget "==0"
			&& strcmp(this->ipbuf, m.ipbuf) == 0;
	}
};

//RAII mutex class
//should not be allowed copyable
class Mutex {
public:
	Mutex() {pthread_mutex_init(&mutex_, NULL);}
	~Mutex() {pthread_mutex_destroy(&mutex_);}
	void lock() {pthread_mutex_lock(&mutex_);}
	void unlock() {pthread_mutex_unlock(&mutex_);}
private:
	pthread_mutex_t mutex_;
};

class MutexLock {
public:
	MutexLock(Mutex &mutex):mutex_(mutex) {mutex_.lock();}
	~MutexLock() {mutex_.unlock();}
private:
	//pay attention mutex_ is a ref, not an object
	Mutex &mutex_;
};

class TerminalSize {
public:
	TerminalSize() :width(80){
		struct winsize w;
		if (ioctl(0, TIOCGWINSZ, &w) < 0) {
			//sys_err("get terminal width failed");
			perror("get terminal width failed");
		}
		width = w.ws_col;	
	}
	int width;
};

//a thread safe teble class
class MetaTable {
public:
	void push_back(Meta m) {
		MutexLock lock(mutex_);
		for (const auto &item : table_) {
			if (m == item) return;
		}
		table_.push_back(m);
	}

	void remove(const Meta &m) {
		for (int i = 0; i < size(); i++) {
			if (table_[i] == m) {
				table_.erase(table_.begin() + i);
				break;
			}
		}
	}
	
	//fix me: efficiency should be mentioned
	void removeHas(char *ipbuf) {
		while(true) {
			int i = 0;
			for (; i < size(); i++) {
				if (strcmp(ipbuf, table_[i].ipbuf) == 0) {
					break;
				}
			}
			if (i < size()) {
				table_.erase(table_.begin() + i);
			}
			else {
				break;
			}
		}
	}

	void clear() {table_.clear();}
	
	int size() const {return table_.size();}

	Meta& operator[](int i) {
		MutexLock lock(mutex_);
		if (i >= table_.size()) {
			std::cout << "index too large!" << std::endl;
		}
		return table_[i];
	}
	void display() {
		TerminalSize ts;
		int terminalwd = ts.width;
		int wnum = terminalwd * 0.05,
			wname = terminalwd * 0.35,//ts.width * 0.4, 
			wlen = terminalwd * 0.15,//ts.width * 0.15, 
			wtype = terminalwd * 0.15,//ts.width * 0.15, 
			wip = terminalwd * 0.3;//ts.width * 0.3;
		printf("%-*s%-*s%-*s%-*s%-*s\n"
				, wnum, "num"
				, wname, "file-name"
				, wlen, "size(bytes)"
				, wtype, "type"
				, wip, "ip-address");

		MutexLock lock(mutex_);
		for (int i = 0; i < table_.size(); i++) {
			const Meta &x = table_[i];
			switch(x.type) {
				case fregular: printf("%-*d%-*s%-*lld%-*s%-*s\n"
									   	, wnum, i
									   	, wname, x.path.c_str()
									   	, wlen, x.len
									   	, wtype, "regular"
									   	, wip, x.ipbuf);break;
				case fdirectory: printf("%-*d%-*s%-*lld%-*s%-*s\n"
										, wnum, i
										, wname, x.path.c_str()
										, wlen, x.len
										, wtype, "directory"
										, wip, x.ipbuf);break;
			}
		}

	}

	std::vector<char> toString() const {
		//MutexLock lock(mutex_);
		std::vector<char> vec;
		for (const auto &m : table_) {
			int n = m.path.size() + 20 + 2 + 3; 
			int nbytes;
			std::vector<char> buf(n, 0);
			// 0 is automatic appended
			nbytes = sprintf(&buf[0], "%s%c%lld%c%d", m.path.c_str(), '\0', m.len, '\0', m.type);
			//nbytes exclude '\0', so plus 1 is necessary
			vec.insert(vec.end(), buf.begin(), buf.begin() + nbytes + 1);
		}
		return vec;
	}
private:
	std::vector<Meta> table_;
	Mutex mutex_;
};

MetaTable localMeta;
MetaTable globalMeta;
//MetaTable removableMeta;

class TcpConnection {
public:
	TcpConnection(int fd, const struct sockaddr_in &peeraddr) :fd_(fd), peeraddr_(peeraddr) {}
	~TcpConnection() {close(fd_);}
	
	int sendFile() {
		const int n = 4096;
		char buf[n] = {0};
		int nbytes = 0;
		int i = 0;

		if (read(fd_, buf, n) < 0) {
			sys_err("read file name from socket fail");
		}
		for (; i < localMeta.size(); i++) {
			if(strcmp(localMeta[i].path.c_str(), buf) == 0) {
				break;
			}
		}
		if (i == localMeta.size()) {
			sys_err("no local shared file name");
		}
		ll len = htonll(localMeta[i].len);
		if (write(fd_, &len, sizeof(len)) < 0) {
			sys_err("write file length to socket failed");
		}

		int localfd = 0;
		if((localfd = open(buf, O_RDONLY)) < 0) {
			sys_err("open local file failed");
		}
		while (true) {
			if((nbytes = read(localfd, buf, n)) < 0) {
				sys_err("read from local file failed");
			}
			else if (nbytes == 0) {
				break;
			}

			if (write(fd_, buf, nbytes) != nbytes) {
				sys_err("write file content to socket failed");
			}
		}
		return 0;
	}

	int receiveFile(const char *path) {
		const int n = 4096;
		char buf[n] = {0};
		strcpy(buf, path);
		int localfd = 0;
		if ((localfd = open(basename(buf), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
			sys_err("creat local file failed");
		}

		ll len = 0, offset = 0;
		int nbytes = 0;
		memset(buf, 0, sizeof(buf));
		if (read(fd_, &len, sizeof(len)) < 0) {
			sys_err("read file length failed");
		}
		len = ntohll(len);
		int freq = 100, i = 1;
		struct timespec start[2];
		struct timespec end[2];
		double chunk = 0;
		if (clock_gettime(CLOCK_REALTIME, &start[0]) < 0) {
			sys_err("clock_gettime failed");
		}
		while(offset != len) {
			if (i % freq == 1) {
				if(clock_gettime(CLOCK_REALTIME, &start[1]) < 0) {
					sys_err("clock_gettime failed");
				}
			}
			if((nbytes = read(fd_, buf, n)) < 0) {
				sys_err("read file from socket failed!");
			}
			
			if (write(localfd, buf, nbytes) != nbytes) {
				sys_err("write to local file failed");
			}
			chunk += nbytes;
			offset += nbytes;
			if (i % freq == 0) {
				if (clock_gettime(CLOCK_REALTIME, &end[1]) < 0) {
					sys_err("clock_gettime failed");
				}
				displaySpeed(start[1], end[1], chunk, len, offset);
				chunk = 0;	
			}
			++i;
		}
		if (clock_gettime(CLOCK_REALTIME, &end[0]) < 0) {
			sys_err("clock_gettime failed");
		}
		displaySpeed(start[0], end[0], offset, len, offset);
		std::cout << "DOWNLOADING " << path << " FINISHED!" << std::endl;
		return 0;
	}

	int sendMeta(const MetaTable &table) {
		std::vector<char> vec = table.toString();
		int n = vec.size();
		int netn = htonl(n);
		if (write(fd_, &netn, sizeof(netn)) < 0) {
			sys_err("write to buf size to socket failed");
		}
		if (write(fd_, &vec[0], n) != n) {
			sys_err("write meta data to socket failed");
		}
	}

	
	int receiveMeta(MetaTable &table) {
		int n = 0, nbytes = 0;
		if (read(fd_, &n, sizeof(n)) < 0) {
			sys_err("read buf len failed");
		}
		n = ntohl(n);
		std::vector<char> buf(n);
		int offset = 0;
		while (offset != n) {
			char *ptr = &buf[0] + offset;
			if ((nbytes = read(fd_, ptr, n - offset)) < 0) {
				sys_err("read meta data from remote machine failed");
			}
			offset += nbytes;
		}
		char *ptr = &buf[0];	
		while(ptr < &buf[0] + n) {
			Meta m;
			m.path.append(ptr);
			ptr = strchr(ptr, '\0');
			++ptr;
			m.len = atoll(ptr);
			ptr = strchr(ptr, '\0');
			++ptr;
			m.type = atoi(ptr);
			ptr = strchr(ptr, '\0');
			++ptr;
			inet_ntop(AF_INET, &peeraddr_.sin_addr, m.ipbuf, sizeof(m.ipbuf));
			table.push_back(m);
		}
		return 0;
	}

	int send(const char *buf, int n) {
		if (write(fd_, buf, n) < 0) {
			sys_err("send message via tcp socket failed");
		}
	}

	// this receive is for file path receive not for general receive;
	// data may be uncomplete if data size is large then 1024
	std::string receive() {
		const int n = 1024;
		char buf[n] = {0};
		std::string str;
		if (read(fd_, buf, sizeof(buf)) < 0) {
			perror("read message via tcp socket failed");
			return str;
		}
		str.append(buf);
		return str;
	}
	
private:
	int displaySpeed( const struct timespec &start, const struct timespec &end, 
		double chunk, double total, double offset) {

		const double nano = 1e9;
		const int gx = 1e9, mx = 1e6, kx = 1e3, byte = 8;
		double rate = (chunk)/(end.tv_nsec/nano + end.tv_sec - start.tv_sec - start.tv_nsec/nano);
		int percent = 100 * (offset / total);
		TerminalSize ts;
		int n = ts.width - 20;
		const std::vector<char> stubs(n, '-');
		const std::vector<char> hashs(n, '#');
		int cstub = stubs.size() * ((double)percent / 100);
		//normally rate cannot exceed 999 g/s
		if (rate > gx) {
			printf("\r[%6.2lf g/s][%.*s%.*s][%d%%]", rate/gx, cstub, &hashs[0], n - cstub, &stubs[0], percent);
		}
		else if (rate > mx) {
			printf("\r[%6.2lf m/s][%.*s%.*s][%d%%]", rate/mx, cstub, &hashs[0], n - cstub, &stubs[0], percent);
		}
		else if (rate > kx) {
			printf("\r[%6.2lf k/s][%.*s%.*s][%d%%]", rate/kx, cstub, &hashs[0], n - cstub, &stubs[0], percent);
		}
		else {
			printf("\r[%6.2lf b/s][%.*s%.*s][%d%%]", rate, cstub, &hashs[0], n - cstub, &stubs[0], percent);
		}
		return 0;
	}
	static const int len = 1024;
	int fd_;
	struct sockaddr_in peeraddr_;
	//socklen_t len_;
};

class BaseTcp {
public:
	BaseTcp() :connection_(NULL){}
	int sendMeta(const MetaTable &table) {return connection_->sendMeta(table);}
	int receiveMeta(MetaTable &table) {return connection_->receiveMeta(table);}
	int send(char *buf, int n) {return connection_->send(buf, n);}
	std::string receive() {return connection_->receive();}
	int getFd() {return fd_;}
	virtual ~BaseTcp() {
		if (connection_) {delete connection_; connection_ = NULL; close(fd_);}
	}
protected:
	int fd_;
	TcpConnection *connection_;
};

class TcpServer : public BaseTcp{
public:
	TcpServer(in_port_t port):port_(port) {
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port_);

		if ((fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("initialize socket fd failed");
		}

		if (bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
			perror("bind server to port failed");
		}

		if (listen(fd_, backlog) < 0) {
			perror("listen to port failed");
		}
	}

	void establishConnection() {
		//shutdown last opened connection
		if (connection_) {delete connection_; connection_ = NULL;}

		int fd = 0;
		struct sockaddr_in peeraddr;
		socklen_t len = sizeof(peeraddr);
		if ((fd = accept(fd_, (struct sockaddr *)&peeraddr, &len)) < 0) {
			perror("establish connection failed");
			return;
		}

		connection_ = new TcpConnection(fd, peeraddr);
	}

	int sendFile() { return connection_->sendFile(); }
private:
	in_port_t port_;
	static const int backlog = 5;
};

class TcpClient : public BaseTcp{
public:

	TcpClient(const char *ipstr, int port) {
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		inet_pton(AF_INET, ipstr, &addr.sin_addr);
		addr.sin_port = htons(port);

		if ((fd_ = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("initialize socket fd_ failed");
		}

		if (connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
			perror("connect to remote server failed");
		}
		//establishConnection();
		connection_ = new TcpConnection(fd_, addr);
	}

	TcpClient(const sockaddr_in &addr) {
		if ((fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			perror("initialize socket fd failed");
		}	

		if (connect(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
			perror("connect to remote server failed");
		}
		//establishConnection();
		connection_ = new TcpConnection(fd_, addr);
	}


	int requestFile(const char *filepath) {
		connection_->send(filepath, strlen(filepath));
		connection_->receiveFile(filepath);
	}
};

// pay attention udp server only used to multicast information
class MUdpServer {
public:
	MUdpServer(in_port_t port) :port_(port) {
		if ((fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			perror("create msgfd failed");
		}
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port_);

		struct ip_mreq mreq;
		inet_pton(AF_INET, mip, &mreq.imr_multiaddr);
		mreq.imr_interface.s_addr = htonl(INADDR_ANY);

		if(setsockopt(fd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
			perror("add to group faild");
		}

		if (bind(fd_, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
			perror("bind ctlport to fd[0] failed");
		}
	}

	int receive(char *buf, int n, struct sockaddr_in &addr, socklen_t &len) {
		int nbytes = 0;
		if ((nbytes = recvfrom(fd_, buf, n, 0, (struct sockaddr*)&addr, &len)) < 0) {
			sys_err("receive message failed");
		}
		return nbytes;
	}
	int getFd() { return fd_; }
private:
	in_port_t port_;
	int fd_;
};

class UdpClient {
public:
	UdpClient(const char *ipstr, in_port_t port) {
		if ((fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
			//sys_err("initialize udp socket failed");
			perror("initialize udp socket failed");
		}

		unsigned char flag = 0;
		if (setsockopt(fd_, IPPROTO_IP, IP_MULTICAST_LOOP, &flag, sizeof(flag)) < 0) {
			perror("turn off multicast loop failed");
		}

		memset(&addr_, 0, sizeof(addr_));
		addr_.sin_family = AF_INET;
		inet_pton(AF_INET, ipstr, &addr_.sin_addr);
		addr_.sin_port = htons(port);
	}
	int send(const char *buf, int n) {
		if (sendto(fd_, buf, n, 0, (struct sockaddr*)&addr_, sizeof(addr_)) < 0) {
			sys_err("send string via udp failed");
		}
		return 0;
	}
private:
	int fd_;
	struct sockaddr_in addr_;
};

int backGroundFun() {
	const char helloMsg[] = "hello";
	TcpServer metaServer(metaport), fileServer(fileport);
	UdpClient msgClient(mip, msgport);

	// msgClient must fist called then msgServer initialized
	msgClient.send(helloMsg, strlen(helloMsg));

	MUdpServer msgServer(msgport);

	struct pollfd pollbuf[3];
	pollbuf[0].fd = msgServer.getFd();
	pollbuf[0].events = POLLIN;
	pollbuf[1].fd = metaServer.getFd();
	pollbuf[1].events = POLLIN;
	pollbuf[2].fd = fileServer.getFd();
	pollbuf[2].events = POLLIN;

	const int n = 1024;//buffer size;
	char buf[n] = {0};
	int nbytes = 0;

	while (true) {
		if (poll(pollbuf, 3, -1) < 0) {
			sys_err("call poll failed");
		}

		if (pollbuf[0].revents & POLLIN) {
			struct sockaddr_in addr;
			socklen_t len = sizeof(addr);
			memset(&addr, 0, sizeof(addr));
			memset(buf, 0, n);
			nbytes = msgServer.receive(buf, n, addr, len);
			addr.sin_port = htons(metaport);
			if (strcmp(buf, "hello") == 0) {
				TcpClient metaClient(addr);
				metaClient.receiveMeta(globalMeta);
				metaClient.sendMeta(localMeta);
			}
			else if (strcmp(buf, "update") == 0) {
				TcpClient metaClient(addr);
				MetaTable updatedMeta;
				metaClient.receiveMeta(updatedMeta);
				//std::vector<char> ipbuf(16, 0);
				char ipbuf[16];
				inet_ntop(AF_INET, &addr.sin_addr, &ipbuf[0], sizeof(ipbuf));
				globalMeta.removeHas(&ipbuf[0]);
				for (int i = 0; i < updatedMeta.size(); i++) {
					globalMeta.push_back(updatedMeta[i]);
				}
				MetaTable zeroMeta;
				metaClient.sendMeta(zeroMeta);
			}
			else if (strcmp(buf, "exit") == 0) {
				char ipbuf[16];
				inet_ntop(AF_INET, &addr.sin_addr, &ipbuf[0], sizeof(ipbuf));
				globalMeta.removeHas(&ipbuf[0]);	
			}
		}

		if (pollbuf[1].revents & POLLIN) {
			metaServer.establishConnection();
			metaServer.sendMeta(localMeta);
			metaServer.receiveMeta(globalMeta);
		}

		if (pollbuf[2].revents & POLLIN) {
			fileServer.establishConnection();
			fileServer.sendFile();	
		}
	}
	return 0;
}

class Command {
public:
	Command(char *str) :i(1){
		char *ptr = trimstr(str);
		std::string command(ptr);
		std::istringstream is(command);
		copy(std::istream_iterator<std::string>(is),
			 std::istream_iterator<std::string>(),
			 std::back_inserter(argv));
	}
	std::string getCommand() {return argv.front();}
	std::string nextArg() {
		if(i < argv.size()) {
			return argv[i++];
		}
		else {
			return std::string();
		}
	}
private:
	char *trimstr(char *ptr) {
		while (isspace(*ptr)) ++ptr;
		char *end = ptr + strlen(ptr) - 1;
		while (end > ptr && isspace(*end)) --end;
		*(++end) = '\0';
		return ptr;
	}
	int i;
	std::vector<std::string> argv;
};


Meta generateMeta(std::string path) {
	struct stat buf;
	Meta t;
	if (stat(path.c_str(), &buf) < 0) {
		perror("get file stat failed");
		return t;
	}
	else {
		if (S_ISREG(buf.st_mode)) {
			t.type = fregular;
			t.len = buf.st_size;
		}
		else if (S_ISDIR(buf.st_mode)) {
			t.type = fdirectory;
			t.len = buf.st_size;
		}
	}
	t.path = path;
	return t;
}

void handler(int dummy) {
	UdpClient msgClient(mip, msgport);
	msgClient.send("exit", strlen("exit"));
	exit(0);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "help: share <path-to-file>|<path-to-folder>..." << std::endl;
	}	
	else {
		for (int i = 1; i < argc; i++) {
			localMeta.push_back(generateMeta(std::string(argv[i])));
		}
	}

	pthread_t backGroundThread;
	if (pthread_create(&backGroundThread, NULL, (void*(*)(void*))backGroundFun, NULL) < 0) {
		sys_err("create launch thread failed");
	}

	signal(SIGINT, handler);
	while (true) {
		std::cout << ">" << std::flush;
		const int n = 1024;
		char buf[n] = {0};
		if(read(STDIN_FILENO, buf, sizeof(buf)) < 0) {
			sys_err("get stdin failed");
		}

		Command command(buf);
		if (command.getCommand() == "list") {
			globalMeta.display();
		}
		else if (command.getCommand() == "exit") {
			//localMeta.clear();
			UdpClient msgClient(mip, msgport);
			msgClient.send("exit", strlen("exit"));
			break;
		}
		else if (command.getCommand() == "download") {
			while (true) {
				std::string arg = command.nextArg();
				if (arg.size() == 0) break;
				for (int i = 0; i < globalMeta.size(); i++) {
					const auto &m = globalMeta[i];
					if (m.path == arg) {
						TcpClient fileClient(m.ipbuf, fileport);
						fileClient.requestFile(m.path.c_str());
						break;
					}
				}
			}
		}
		else if (command.getCommand() == "add") {
			while (true) {
				std::string arg = command.nextArg();
				if (arg.size() == 0) break;
				localMeta.push_back(generateMeta(arg));
			}
			UdpClient msgClient(mip, msgport);
			msgClient.send("update", strlen("update"));
		}
		else if (command.getCommand() == "remove") {
			while (true) {
				std::string arg = command.nextArg();
				if (arg.size() == 0) break;
				localMeta.remove(generateMeta(arg));
			}
			UdpClient msgClient(mip, msgport);
			msgClient.send("update", strlen("update"));
		}
	}
	return 0;
}
