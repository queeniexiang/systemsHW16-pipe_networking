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
  char msg[] =  "Client received: How can I SERVE you?\n"; //WHY AM I SO FUNNY XD
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
  int buffer[BUFFER_SIZE];
  char handshake[HANDSHAKE_BUFFER_SIZE] = "priv"; // set name for the private fifo
  int wkp = open("WKP", O_WRONLY); // open the well known pipe created by the server
  int write_ts_status = write(wkp, handshake, sizeof(handshake)); // write the name of the private fifo so the server can access it
  if (write_ts_status >= 0) {
    printf("Succesfully sent server name of private fifo!\n");
  }
    
  printf("\nEstablishing private fifo..\n"); 
  printf("Name of private fifo: %s\n", handshake);// print name of private fifo
  mkfifo(handshake, 0664); // make the pipe
  int private_fifo = open(handshake, O_RDWR); // open the read end of private fifo
  int s = read(private_fifo, buffer, sizeof(buffer));// check for first handshake message
  if (s != -1) {
    printf("Succesfully read message from server!\n");
    return private_fifo;
  }
  
  else {
     printf("THE SERVER DIDN'T GET TO ME, 0 STARS!\n");
      return -1;
  }

  return 0;
}
 

int client_to_server_msg(int pipe_fd) {
  int buffer[BUFFER_SIZE];
  char user_input[10000];
  while (fgets(user_input, sizeof(user_input), stdin) != NULL) {
    user_input[strlen(user_input)-1] = '\0';
    printf("User input: %s\n", user_input);

    if (pipe_fd == -1) {
      printf("Pipe wasn't established properly... :( Exiting!\n");
      return -1;
    }
    else {
      int w = write(pipe_fd, user_input, sizeof(user_input));
      if (w != -1) { // if there is a message send a second message
	printf("Succesfully sent message to server!\n"); 
      }
    
      else {
	printf("THE SERVER DIDN'T GET TO ME, 0 STARS!\n");
	return -1;
      }
    }
    
    close(pipe_fd);
    
  }
  
  return 0;
}

    
