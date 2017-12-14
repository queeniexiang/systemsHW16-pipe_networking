#include "pipe_networking.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// HANDSHAKE_BUFFER_SIZE is defined in pipe_networking.h
// BUFFER_SIZE is defined in pipe_networking.h

/*=========================
  server_handshake
  Args_client

  Performs the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  char handshake[HANDSHAKE_BUFFER_SIZE]; //string that stores the name of the private fifo to be sent
  mkfifo("WKP", 0664); // create the well known pipe
  int wkp = open("WKP", O_RDONLY); // open it. ***IMPORTANT*** it blocks until the client writes to it
  read(wkp, handshake, sizeof(handshake)); // after client has written to it, gets the private fifo name
  printf("%s\n", handshake); // print the name of the private fifo
  int private_fifo = open(handshake, O_WRONLY); // open the write end of the pipe
  *to_client = private_fifo;
  char msg[] =  "Client received: How can I SERVE you?"; //WHY AM I SO FUNNY XD
  write(private_fifo, msg, sizeof(msg)); //sends first handshake message
  char buffer[BUFFER_SIZE];
  int s = read(wkp, buffer, sizeof(buffer)); //gets second handshake message
  if (s != -1) { // check whether the connection was established
    printf("Connection with client successfully established\n");
  }
  remove("WKP"); //remove the WKP so no other client can access it
  return wkp;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  char handshake[HANDSHAKE_BUFFER_SIZE] = "priv"; // set name for the private fifo
  int wkp = open("WKP", O_WRONLY); // open the well known pipe created by the server
  // write the name of the private fifo so the server can access it
   // print name of private fifo
  mkfifo(handshake, 0664); // make the pipe
   // open the read end of private fifo
  int buffer[BUFFER_SIZE];
  // check for first handshake message
  if (s != -1) { // if there is a message send a second message
    //sends second handshake message
  }
  else {
    printf("THE SERVER DIDN'T GET TO ME, 0 STARS!\n");
  }
  *to_server = wkp;
  return private_fifo;
}
