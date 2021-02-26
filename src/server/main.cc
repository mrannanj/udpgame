#include "server/server.h"
#include "common/util/die.h"

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

int quitPipe[2];

void handle_sigint(int) {
	char c = 'q';
	if (-1 == write(quitPipe[1], &c, 1))
		die("write");
}

int main(void) {
	if (-1 == pipe(quitPipe))
		die("pipe");
	if (-1 == fcntl(quitPipe[0], F_SETFL,
			fcntl(quitPipe[0], F_GETFL) | O_NONBLOCK))
		die("fcntl");
	if (SIG_ERR == signal(SIGINT, handle_sigint))
		die("signal");

	Server server(quitPipe[0]);
	server.init();
	server.serve();

	return 0;
}
