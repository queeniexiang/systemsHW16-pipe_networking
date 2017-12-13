#include "pipe_networking.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*=========================
  server_handshake
  Args_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char buffer[10000]; 
  mkfifo("WKP", 0664);
  int fd = open("WKP", O_RDONLY);
  read(fd, buffer, sizeof(100000));
  
  
  unlink("WKP");
  
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  mkfifo("private_fifo", 0664);
  int fd = open("WKP", O_WRONLY);
  write(fd, "private_fifo", 100000);
  close(fd); 
}


int main() {
  int * chr; 
  server_handshake(chr);
}
