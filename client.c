#include "pipe_networking.h"



int main() {

  int to_server; //WKP. Write to this
  int from_server; // private FIFO. Read from this

  from_server = client_handshake( &to_server );
  char buffer[BUFFER_SIZE];
  printf("enter text here: \n");
  while (fgets(buffer, sizeof(buffer), stdin)) {
    if (strcmp(buffer, "exit\n") == 0) { // when user wants to exit
      close(from_server);
      close(to_server);
      exit(0);
    }
    printf("User input: %s\n", buffer); // print uesr input
    // takes user input and sends it to server. Also does error handling
    if (write(to_server, buffer, sizeof(buffer)) == -1) {
      printf("ERROR: %s\n", strerror(errno));
    }
    if (read(from_server, buffer, sizeof(buffer)) == -1) { //reads message sent by server
      printf("ERROR: %s\n", strerror(errno));
    }
    else {
      printf("server: %s\n", buffer);
    }
  }
}
