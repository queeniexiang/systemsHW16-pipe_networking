#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  int sent_msg_status; 

  from_server = client_handshake( &to_server );
  sent_msg_status = client_to_server_msg(from_server);
  printf("Was message sent to server succesfully? If yes, 0. If not, -1.\n");
  printf("Message status: %d\n", sent_msg_status);
  
}
