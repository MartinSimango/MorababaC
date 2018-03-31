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

   
GAME_NETWORK_DATA game_data;

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
static int get_player_id(){
   
    //game_data->INSTRUCTION=CONNECTED;
    int id;
    write(SOCK_FD,&id,sizeof(id));
    read(SOCK_FD,&id,sizeof(id));
    return id;
    

}
static void  processInstructionFromServer(GAME * Morabaraba){
        POINT_ toPoint;
        POINT_ fromPoint;
        switch(game_data.SERVER_INSTRUCTION){
            case MOVE_PIECE:
             

                fromPoint.let=game_data.fromLet;
                fromPoint.num=game_data.fromNum; 
                toPoint.let=game_data.toLet;
                toPoint.num=game_data.toNum;
                printf("%s moved from (%c,%d) ",Morabaraba->currentPlayer->name,game_data.fromLet,game_data.fromNum);
                printf("to (%c,%d)\n",game_data.toLet,game_data.toNum);
                Game__UpdatePlayer(Morabaraba,&fromPoint,&toPoint,Morabaraba->currentPlayer);
                
            break;
            case DO_NOTHING:
                break;
            default:
                printf("Invalid instruction %d!\n",game_data.SERVER_INSTRUCTION);
                break;


        }

}
static void readFromServer(){

        read(SOCK_FD,&(game_data.CLIENT_INSTRUCTION),sizeof(game_data.CLIENT_INSTRUCTION));
        read(SOCK_FD,&(game_data.SERVER_INSTRUCTION),sizeof(game_data.SERVER_INSTRUCTION));
        read(SOCK_FD,&(game_data.current_player_id) ,sizeof(game_data.current_player_id));
        read(SOCK_FD,&(game_data.lastest_player_id),sizeof(game_data.lastest_player_id));
        read(SOCK_FD,&(game_data.fromLet),sizeof(game_data.fromLet));
        read(SOCK_FD,&(game_data.fromNum),sizeof(game_data.fromNum));
        read(SOCK_FD,&(game_data.toLet),sizeof(game_data.toLet));
        read(SOCK_FD,&(game_data.toNum), sizeof(game_data.toNum));

}
static void writeToServer(){

        write(SOCK_FD,&(game_data.CLIENT_INSTRUCTION),sizeof(game_data.CLIENT_INSTRUCTION));
        write(SOCK_FD,&(game_data.SERVER_INSTRUCTION),sizeof(game_data.SERVER_INSTRUCTION));
        write(SOCK_FD,&(game_data.current_player_id) ,sizeof(game_data.current_player_id));
        write(SOCK_FD,&(game_data.lastest_player_id),sizeof(game_data.lastest_player_id));
        write(SOCK_FD,&(game_data.fromLet),sizeof(game_data.fromLet));
        write(SOCK_FD,&(game_data.fromNum),sizeof(game_data.fromNum));
        write(SOCK_FD,&(game_data.toLet),sizeof(game_data.toLet));
        write(SOCK_FD,&(game_data.toNum), sizeof(game_data.toNum));
}
static void sendInstruction(){

        writeToServer();

        readFromServer();
}
static void run_game(GAME * Morabaraba){
    int i=0;
    Game__PrintBoard(Morabaraba);
    if(Morabaraba->whosTurn==PLAYER_ID){
        
        POINT_ toPoint;
        POINT_ fromPoint; 
       
      
        getPlayerMove(Morabaraba,&fromPoint,&toPoint, Morabaraba->currentPlayer); //fromPoint and toPoint returned must be valid
        
        game_data.fromLet= fromPoint.let;
        game_data.fromNum= fromPoint.num;
        game_data.toLet= toPoint.let;
        game_data.toNum= toPoint.num;
        
        
        Game__UpdatePlayer(Morabaraba,&fromPoint,&toPoint,Morabaraba->currentPlayer);
        game_data.CLIENT_INSTRUCTION=PLAYER_MOVE;
        sendInstruction();   //tell server that you moved
        
         
       /* if(game_data->INSTRUCTION==MILLFORMED){
            Game__PrintBoard(Morabaraba);
            killCow()
        }*/
        //write()
    }
    else{
        printf("Currently %s's turn\n",Morabaraba->currentPlayer->name);
        //wait for server to return enemy player move
        readFromServer();
         
        
        
        
    }
    processInstructionFromServer(Morabaraba);
     

    run_game(Morabaraba);

}

static void startGameNetwork(){
    
    if(!connect_to_server("127.0.0.1")){
        perror("oops: Failed to connect to server!");
        exit(1);
    }
    
    printf("Connected\n");
    
     

    game_data.CLIENT_INSTRUCTION=0;
    game_data.SERVER_INSTRUCTION=0;
    game_data.current_player_id=0;
    game_data.lastest_player_id=0;
    game_data.fromLet=' ';
    game_data.fromNum=0;
    game_data.toLet=' ';
    game_data.toNum=0;






    PLAYER_ID= get_player_id();

    printf("You are player %d\n",(PLAYER_ID+1));
    if(PLAYER_ID==0)
        printf("Waiting for second player...\n");

    //wait for the game to start

    read(SOCK_FD,&(game_data.SERVER_INSTRUCTION),sizeof(game_data.SERVER_INSTRUCTION));
    printf("Game can start!\n");
    
    //wait_game_start(request_data); //get the game from the server

   
    
    if(game_data.SERVER_INSTRUCTION==GAME_START){
        GAME * Morabaraba = (GAME *) malloc(sizeof(GAME));
       	init__Game(Morabaraba,"Player 1","Player 2");
        run_game(Morabaraba); //start the game
    }
    else{
        perror("Game failed to start!");
    }
   
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


