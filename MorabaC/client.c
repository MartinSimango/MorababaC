#include "stdafx.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "server_client.h"

static int SOCK_FD;
static int PLAYER_ID;
static int NETWORK=1;
static struct sockaddr_in SERVER_ADDRESS;

static int connect_to_server(const char * ip_address){
   //create socket for client
    SOCK_FD=socket(AF_INET,SOCK_STREAM,0);
    SERVER_ADDRESS.sin_family=AF_INET;	//
    SERVER_ADDRESS.sin_addr.s_addr= inet_addr(ip_address); //ip address of server
    SERVER_ADDRESS.sin_port=htons(SERVER__PORT); //random port to connect to
    
    
    int result = connect(SOCK_FD,(struct sockaddr *)&SERVER_ADDRESS, sizeof(SERVER_ADDRESS));
    
    if(result==-1)
        return 0;
    
    return 1;
}
static int get_player_id(GAME_NETWORK_DATA * game_data){
   
    game_data->INSTRUCTION=CONNECTED;
    write(SOCK_FD,game_data,sizeof(GAME_NETWORK_DATA));
    read(SOCK_FD,game_data,sizeof(GAME_NETWORK_DATA));
    return game_data->lastest_player_id;
    

}
static void get_game(GAME_NETWORK_DATA * game_data){ 

    game_data->INSTRUCTION=GETGAME;
    write(SOCK_FD,game_data,sizeof(GAME_NETWORK_DATA));
    read(SOCK_FD,game_data,sizeof(GAME_NETWORK_DATA));
}
static void run_game(GAME_NETWORK_DATA * game_data){
    GAME *Morabaraba= game_data->game;
    Game__PrintBoard(Morabaraba);
    if(Morabaraba->currentPlayer->id==PLAYER_ID){
        POINT_PTR toPoint = (struct Point*) malloc(sizeof(struct Point));
        POINT_PTR fromPoint = (struct Point*) malloc(sizeof(struct Point));
        
        getPlayerMove(Morabaraba,fromPoint, toPoint, Morabaraba->currentPlayer); //fromPoint and toPoint returned must be valid
        game_data->INSTRUCTION=MOVEMADE;
       /* write(SOCK_FD,game_data,sizeof(GAME_NETWORK_DATA));
        read(SOCK_FD,game_data,sizeof(GAME_NETWORK_DATA));
        if(game_data->INSTRUCTION==MILLFORMED){
            killCow()
        }*/
        //write()
    }
    else{
        printf("Currently player %s's turn\n",Morabaraba->currentPlayer->name);
    
        
    }

}

static void startGameNetwork(){
    if(!connect_to_server("127.0.0.1")){
        perror("oops: Failed to connect to server!");
        exit(1);
    }
    
    printf("Connected\n");

    GAME_NETWORK_DATA *request_data =malloc(sizeof(GAME_NETWORK_DATA));

    PLAYER_ID= get_player_id(request_data);
    printf("You are player %d\n",(PLAYER_ID+1));
    printf("Waiting for second player...\n");
    //wait for the game to start
    read(SOCK_FD,request_data,sizeof(GAME_NETWORK_DATA));

    run_game(request_data);
    
   
    close(SOCK_FD); //close the socket
    exit(0);
}

int main(int argc, char *argv[]){
    #if  defined(__APPLE__) || defined(__unix__)
	setTerminalSettings();
    #endif
    if(NETWORK)
	    startGameNetwork();
    else{
        startGame();
    }

    #if  defined(__APPLE__) || defined(__unix__)
	resetTerminalSettings();
    #elif defined(_WIN32) || defined(WIN32)
	_getch();
    #endif
    

    
}


