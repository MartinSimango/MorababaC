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
static void write_to_player(int i){

    write(PLAYER_SOCK_ID[i],&(network_data.CLIENT_INSTRUCTION),sizeof(network_data.CLIENT_INSTRUCTION));
    write(PLAYER_SOCK_ID[i],&(network_data.SERVER_INSTRUCTION),sizeof(network_data.SERVER_INSTRUCTION));
    write(PLAYER_SOCK_ID[i],&(network_data.current_player_id) ,sizeof(network_data.current_player_id));
    write(PLAYER_SOCK_ID[i],&(network_data.lastest_player_id),sizeof(network_data.lastest_player_id));
    write(PLAYER_SOCK_ID[i],&(network_data.fromLet),sizeof(network_data.fromLet));
    write(PLAYER_SOCK_ID[i],&(network_data.fromNum),sizeof(network_data.fromNum));
    write(PLAYER_SOCK_ID[i],&(network_data.toLet),sizeof(network_data.toLet));
    write(PLAYER_SOCK_ID[i],&(network_data.toNum), sizeof(network_data.toNum));
    


}
static void read_from_player(int i){

    read(PLAYER_SOCK_ID[i],&(network_data.CLIENT_INSTRUCTION),sizeof(network_data.CLIENT_INSTRUCTION));
    read(PLAYER_SOCK_ID[i],&(network_data.SERVER_INSTRUCTION),sizeof(network_data.SERVER_INSTRUCTION));
    read(PLAYER_SOCK_ID[i],&(network_data.current_player_id) ,sizeof(network_data.current_player_id));
    read(PLAYER_SOCK_ID[i],&(network_data.lastest_player_id),sizeof(network_data.lastest_player_id));
    read(PLAYER_SOCK_ID[i],&(network_data.fromLet),sizeof(network_data.fromLet));
    read(PLAYER_SOCK_ID[i],&(network_data.fromNum),sizeof(network_data.fromNum));
    read(PLAYER_SOCK_ID[i],&(network_data.toLet),sizeof(network_data.toLet));
    read(PLAYER_SOCK_ID[i],&(network_data.toNum), sizeof(network_data.toNum));

}
static void process_instruction_fromClient(GAME * Morabaraba){
     POINT_ toPoint;
     POINT_ fromPoint;

     switch(network_data.CLIENT_INSTRUCTION){
        case PLAYER_MOVE:

            
              fromPoint.let=network_data.fromLet;
              fromPoint.num=network_data.fromNum; 
              toPoint.let=network_data.toLet;
              toPoint.num=network_data.toNum;
               
             
              network_data.SERVER_INSTRUCTION= DO_NOTHING;
       write_to_player(Morabaraba->currentPlayer->id);
    
     
              Game__UpdatePlayer(Morabaraba,&fromPoint,&toPoint,Morabaraba->currentPlayer);
              
            printf("Player %d just played\n",(Morabaraba->currentPlayer->id+1));
             network_data.SERVER_INSTRUCTION=MOVE_PIECE;
             write_to_player(Morabaraba->currentPlayer->id);
        
            break;
        case GET_WHOS_TURN:
            network_data.SERVER_INSTRUCTION=DO_NOTHING;
            network_data.current_player_id=Morabaraba->whosTurn;
      
           
        break;
    

        default:
            break;

     }
     //current player has been update locally so just send instruction to enemy player to update the board
     
     
     
     

}

static void sendClientsGame(GAME * Morabaraba){
    
     read_from_player(Morabaraba->currentPlayer->id);
     if(network_data.CLIENT_INSTRUCTION!=PLAYER_MOVE){
    
        process_instruction_fromClient(Morabaraba);
        write_to_player(Morabaraba->currentPlayer->id);
      
        read_from_player(Morabaraba->enemyPlayer->id);
       process_instruction_fromClient(Morabaraba);
     }
     else
     {
        process_instruction_fromClient(Morabaraba);

     }
    

      
    
  }
  // printf("Intr %d\n",network_data.CLIENT_INSTRUCTION);
 
        
static void runGameServer(GAME*Morabaraba){
       Game__PrintBoard(Morabaraba);
     sendClientsGame(Morabaraba);
   //while(1);
     runGameServer(Morabaraba);
     

}



       



    //READ clients request for game to start 
  

static void startGameServer(){
 
    GAME *Morabaraba= (GAME*)malloc(sizeof(GAME)); //to keep track of game states make this an array?
	init__Game(Morabaraba,"Player 1","Player 2");
  

    //waiting for server to send who's turn
    sendClientsGame(Morabaraba);


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
    
    



	while( NUM_PLAYERS<2 ){
        int player_id;
		printf("Waiting for clients...\n");
		fflush(stdout);
		client_sockfd = accept(SERVER_SOCK_FD,(struct sockaddr*)&client_address,(socklen_t *)&client_len);
        printf("Player %d connected\n",network_data.lastest_player_id+1);
		PLAYER_SOCK_ID[NUM_PLAYERS]=client_sockfd;

		read(client_sockfd,&player_id,sizeof(player_id));
        player_id=NUM_PLAYERS++;
		
        write(client_sockfd,&player_id,sizeof(player_id));
		
	}
	printf("Game can now Start!\n");
	//tell clients game cant start
    network_data.SERVER_INSTRUCTION=GAME_START;
    write(PLAYER_SOCK_ID[0],&(network_data.SERVER_INSTRUCTION),sizeof(network_data.SERVER_INSTRUCTION));
    write(PLAYER_SOCK_ID[1],&(network_data.SERVER_INSTRUCTION),sizeof(network_data.SERVER_INSTRUCTION));

	startGameServer();

}
