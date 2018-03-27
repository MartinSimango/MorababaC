#include "stdafx.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "server_client.h"

static int SERVER_SOCK_FD;
static int PLAYER_SOCK_ID[2]; //the client_sock
static int NUM_PLAYERS=0;
static struct sockaddr_in SERVER_ADDRESS;
static GAME_NETWORK_DATA network_data;

static void create_server_socket(){
//create the socket
    SERVER_SOCK_FD  = socket(AF_INET,SOCK_STREAM,0);
//create the address for the socket

	SERVER_ADDRESS.sin_family=AF_INET;
	SERVER_ADDRESS.sin_addr.s_addr=htonl(INADDR_ANY); //for byte ordering(htonl and htnos) allow any address to connect
	SERVER_ADDRESS.sin_port=htons(SERVER__PORT);
   
    bind(SERVER_SOCK_FD,(struct sockaddr*)&SERVER_ADDRESS,sizeof(SERVER_ADDRESS));

    
}



static void runGameServer(GAME*Morabaraba){
     
     Game__PrintBoard(Morabaraba);
     POINT_PTR toPoint = (struct Point*) malloc(sizeof(struct Point));
     POINT_PTR fromPoint = (struct Point*) malloc(sizeof(struct Point));
     Game__UpdatePlayer(Morabaraba,fromPoint,toPoint,Morabaraba->currentPlayer);

}
static void startGameServer(){
    
    GAME *Morabaraba= malloc(sizeof(GAME)); //to keep track of game states make this an array?
	init__Game(Morabaraba,"Player 1","Player 2");
    network_data.game=Morabaraba;
    runGameServer(Morabaraba);

}
int main(int argc,char*argv[]){
	
    int client_sockfd;
	int client_len,server_len;
	struct sockaddr_in server_address,client_address;
	
    create_server_socket();
    printf("Server started\n");
    
    listen(SERVER_SOCK_FD,2);
    network_data.lastest_player_id=0;
    client_len=sizeof(client_address);
    
    



	while(1){
		printf("Waiting for clients...\n");
		fflush(stdout);
		client_sockfd = accept(SERVER_SOCK_FD,(struct sockaddr*)&client_address,(socklen_t *)&client_len);
        printf("Player %d connected\n",network_data.lastest_player_id+1);
		PLAYER_SOCK_ID[NUM_PLAYERS]=client_sockfd;
		read(client_sockfd,&network_data,sizeof(network_data));
		network_data.lastest_player_id=NUM_PLAYERS++;
		write(client_sockfd,&network_data,sizeof(network_data));
		if(NUM_PLAYERS==2){
			break;
		}
	}
	printf("Game can now Start!\n");
	//startGame();
	startGameServer();
}
