#include "pipe_networking.h"
#include <ctype.h>

// converts given string to upper case string
void to_upper(char *str) {
  int i = 0;
  while (str[i]) {
    str[i] = toupper(str[i]);
    i++;
  }
}

int main() {

  int to_client; //file descriptor of downstream pipe. Write to this one
  int from_client; //WKP. Read from this one
  from_client = server_handshake( &to_client );
  char buffer[BUFFER_SIZE];
  printf("waiting for message from client...\n" );
  while(1) {
    if(strcmp(buffer, "exit\n") == 0) { //if the user exits by sending exit message
      printf("Server terminated\n");
      close(from_client);
      close(to_client);
      exit(0);
    }
    if(read(from_client, buffer, sizeof(buffer)) == -1) {//read in next message and error handling
      printf("ERROR: %s\n", strerror(errno));
    }
    printf("%s\n", buffer); // print text received
    to_upper(buffer); // edits input text
    printf("msg to be sent: %s\n", buffer);
    if (write(to_client, buffer, sizeof(buffer)) == -1) { // writes edited message to client and error handling
      printf("ERROR: %s\n", strerror(errno));
    }
  }
  return 0;
}
