// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Leaderboard.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>


extern "C" {
	#include "hiredis-win/hiredis.h"
}

#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;


class LeaderboardHandler : virtual public LeaderboardIf {
 public:
  LeaderboardHandler() {
    // Your initialization goes here
  }

  void setHighScore(const int32_t playerId, const int32_t highScore) {
    // Your implementation goes here
    printf("setHighScore\n");
  }

  void getTop20(std::map<int32_t, int32_t> & _return) {
    // Your implementation goes here
    printf("getTop20\n");
  }

};

int main(int argc, char **argv) {

	unsigned int j;
	redisContext *c;
	redisReply *reply;

	struct timeval timeout = { 5, 500000 }; // 5.5 seconds

	WSADATA wsaDataRedis;
	WSAStartup(MAKEWORD(2, 2), &wsaDataRedis);

	c = redisConnectWithTimeout((char*)"127.0.0.1", 6379, timeout);
	if (c->err) {
		printf("Connection error: %s\n", c->errstr);
		printf("May have timed out....\n");
		exit(1);
	}

	redisSetTimeout(c, timeout);

	/* PING server */
	reply = (redisReply *)redisCommand(c, "PING");
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);


	WSAData wsaData;
	int initializationResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (initializationResult != 0) {
		printf("Failed to init winsock %d\n", initializationResult);
		return 1;
	}

  int port = 9090;
  shared_ptr<LeaderboardHandler> handler(new LeaderboardHandler());
  shared_ptr<TProcessor> processor(new LeaderboardProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

