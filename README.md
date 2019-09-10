# UDPSERVER
A non blocking UDP server which handles multiple client simultaneously. libevent is used for managing the FD.
# compilation:
  Just need to do the make in the directory and it will create a binary.
#run
  ./udpserver
# driver

A udp client is added under directory testUdpClient, which can be used to test the server.
To compile the client just do <gcc udpClient.c>
