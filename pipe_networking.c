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
  int status = mkfifo("WKP", 0664);
  printf("Status: %d\n", status); 
  int fd = open("WKP", O_RDONLY);
  printf("fd:%d\n", fd);
  //read(fd, buffer, sizeof(buffer));
  remove("WKP");
  printf("Stuff: %s\n", buffer); 
  
  
  
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
  int status = mkfifo("private_fifo", 0664);


  int fd = open("WKP", O_WRONLY);
  printf("fd:%d\n", fd);

  /* 
  int private_fd = open("private_fifo", O_RDWR);
  printf("private_fd: %d\n", private_fd); 
  write(fd, "private_fifo", 100000);
  close(fd);
 
  remove("private_fifo");
  */
  return 0;
}


int main() {
  int * chr; 
  server_handshake(chr);
  //client_handshake(chr);
  return 0;
}
