#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#define PORT 12345
#define SA struct sockaddr

void Login_Register();
void Channel();
void Creat_Channel();
void join_Channel();
void Chat_Room();
void Send_Message();
void Register();
void Login();
void Refresh();
void Members();
void Leave();
void ConnectToServer();
void logout();
void find_users();
void find_messages();

void red(){
    system("color 04");
}
void blue(){
    system("color 01");
}
void green(){
    system("color 02");
}
void yellow(){
    system("color 06");
}
void purple(){
    system("color 05");
}
void clear(){
    system("@cls||clear");
}
char Token[200];
int client_socket;
struct sockaddr_in servaddr;
struct sockaddr_in server;

int main() {
    while (1)
        Login_Register();
}

void Channel() {
    int Channel_Num;
    purple();
    printf("1: Create Channel\n");
    purple();
    printf("2: Join Channel\n");
    purple();
    printf("3: Logout\n");
    scanf("%d", &Channel_Num);
    switch (Channel_Num){
        case 1:
            Creat_Channel();
            break;
        case 2:
            join_Channel();
            Chat_Room();
            break;
        case 3:
            logout();
            Login_Register();
            break;
    }
}
void logout(){
    char  buffer[300] = "logout ";
    strcat(buffer , Token);
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
}
void Login() {
    char *UserName = (char *) calloc(100, sizeof(char));
    char *PassWord = (char *) calloc(100, sizeof(char));
    blue();
    printf("please login:\nEnter Username\n");
    scanf("%s", UserName);
    blue();
    printf("Enter Password\n");
    scanf("%s", PassWord);
    int n = 6;
    char buffer[300] = "login ";
    strcpy(buffer + 6, UserName);
    buffer[strlen(UserName) + n] = ','; buffer[strlen(UserName) + n + 1] = ' '; n += 2;
    strcpy(buffer + n + strlen(UserName), PassWord);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(cJSON_GetObjectItem(cJSON_Parse(buffer), "type")->valuestring, "Error")) {
        red();
        printf("%s\n", cJSON_GetObjectItem(cJSON_Parse(buffer), "content")->valuestring);
        Login_Register();
    } else {
        strcpy(Token, cJSON_GetObjectItem(cJSON_Parse(buffer), "content")->valuestring);
    }
    free(UserName);
    free(PassWord);
    Channel();
}

void Register() {
    char *UserName = (char *) calloc(100, sizeof(char));
    char *PassWord = (char *) calloc(100, sizeof(char));
    blue();
    printf("Enter Username\n");
    scanf("%s", UserName);
    blue();
    printf("Enter Password\n");
    scanf("%s", PassWord);
    int n = 9;
    char buffer[300] = "register ";
    strcpy(buffer + 9, UserName);
    buffer[strlen(UserName) + n] = ',';
    buffer[strlen(UserName) + n + 1] = ' ';
    n += 2;
    strcpy(buffer + n + strlen(UserName), PassWord);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(cJSON_GetObjectItem(cJSON_Parse(buffer), "type")->valuestring, "Error")) {
        red();
        printf("%s\n", cJSON_GetObjectItem(cJSON_Parse(buffer), "content")->valuestring);
        Login_Register();
    }
    clear();
    green();
    printf("Registeration was successful\n");
    free(UserName);
    free(PassWord);
    Login();
}

void Login_Register() {
    int Register_or_Login_Num;
    blue();
    printf("Account Menu:\n");
    blue();
    printf("1: Register\n");
    blue();
    printf("2: Login\n");
    scanf("%d", &Register_or_Login_Num);
    switch(Register_or_Login_Num){
        case 1:
            Register();
            Channel();
            break;
        case 2:
            Login();
            Channel();
    }
}

void Creat_Channel() {
    char *Channel_name = (char *) calloc(1000, sizeof(char));
    char buffer[2000] = "create channel ";
    yellow();
    printf("please Enter Channel name:\n");
    scanf("%s", Channel_name);
    int n = 15;
    strcpy(buffer + 15, Channel_name);
    buffer[strlen(Channel_name) + n] = ',';
    buffer[strlen(Channel_name) + n + 1] = ' ';
    n += 2;
    strcpy(buffer + n + strlen(Channel_name), Token);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(cJSON_GetObjectItem(cJSON_Parse(buffer), "type")->valuestring, "Error")) {
        red();
        printf("%s\n", cJSON_GetObjectItem(cJSON_Parse(buffer), "content")->valuestring);
        Creat_Channel();
    }
    free(Channel_name);
    Chat_Room();
}

void join_Channel() {
    char* Channel_name = (char *) calloc(1000, sizeof(char));
    char buffer[2000] = "join channel ";
    yellow();
    printf("please Enter Channel name:\n");
    scanf("%s", Channel_name);
    int n = 13;
    strcpy(buffer + 13, Channel_name);
    buffer[strlen(Channel_name) + n] = ',';
    buffer[strlen(Channel_name) + n + 1] = ' ';
    n += 2;
    strcpy(buffer + n + strlen(Channel_name), Token);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(cJSON_GetObjectItem(cJSON_Parse(buffer), "type")->valuestring, "Error")) {
        red();
        printf("%s\n", cJSON_GetObjectItem(cJSON_Parse(buffer), "content")->valuestring);
        Channel();
    }
    free(Channel_name);
}

void Chat_Room() {
    while (1) {
        int Chat_Num;
        purple();
        printf("1: Send Message\n");
        purple();
        printf("2: Refresh\n");
        purple();
        printf("3: Channel Members\n");
        purple();
        printf("4: find users\n");
        purple();
        printf("5: find messages\n");
        purple();
        printf("6: clear\n");
        purple();
        printf("7: Leave Channel\n");
        scanf("%d", &Chat_Num);
        switch (Chat_Num) {
            case 1:
                Send_Message();
                break;
            case 2:
                Refresh();
                break;
            case 3:
                Members();
                break;
            case 4:
                find_users();
                break;
            case 5:
                find_messages();
                break;
            case 6:
                clear();
                break;
            case 7:
                Leave();
        }
    }
}

void Send_Message() {
    char Message[1000 * 100 + 1];
    char buffer[101000] = "send ";
    int n = 5;
    clear();
    yellow();
    printf("your message:\n");
    gets(Message);
    gets(Message);
    strcpy(buffer + 5, Message);
    buffer[strlen(Message) + n] = ','; buffer[strlen(Message) + n + 1] = ' '; n += 2;
    strcpy(buffer + n + strlen(Message), Token);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);
}

void Refresh() {
    char buffer[1000 * 100 + 1] = "refresh ";
    strcpy(buffer + 8, Token);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    recv(client_socket, buffer, sizeof(buffer), 0);
    cJSON *i = NULL;
    cJSON *h = cJSON_Parse(buffer);
    cJSON *content = cJSON_GetObjectItem(h, "content");
    cJSON_ArrayForEach(i, content) {
        if (strcmp(cJSON_GetObjectItem(i, "sender") -> valuestring, "server")) {
            purple();
            printf("%s :", cJSON_GetObjectItem(i, "sender") -> valuestring);
            purple();
            printf("%s\n", cJSON_GetObjectItem(i, "content") -> valuestring);
        }
    }
}

void Members() {
    char buffer[100000] = "channel members ";
    strcpy(buffer + 16, Token);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    recv(client_socket, buffer, sizeof(buffer), 0);
    cJSON *h = cJSON_Parse(buffer);
    printf("members : \n");
    cJSON *content = cJSON_GetObjectItem(h, "content");
    for (int j = 0; j < cJSON_GetArraySize(content); j++) {
        purple();
        printf("%s\n", cJSON_GetArrayItem(content, j) -> valuestring);
    }
}

void Leave() {
    char buffer[220] = "leave ";
    strcpy(buffer + 6, Token);
    buffer[strlen(buffer)] = '\n';
    ConnectToServer();
    send(client_socket, buffer, sizeof(buffer), 0);
    recv(client_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(cJSON_GetObjectItem(cJSON_Parse(buffer), "type")->valuestring, "Error")) {
        red();
        printf("%s\n", cJSON_GetObjectItem(cJSON_Parse(buffer), "content")->valuestring);
        Chat_Room();
    }
    Channel();
}

void find_users(){
    char buffer[200] = "find_user ";
    char username[200];
    yellow();
    printf("please enter username : \n");
    scanf("%s",username);
    strcpy(buffer + 10 , username);
    strcat(buffer , " ");
    strcat(buffer , Token);
    strcat(buffer , "\n");
    ConnectToServer();
    send(client_socket , buffer , sizeof(buffer) , 0);
    recv(client_socket, buffer, sizeof(buffer), 0);
    yellow();
    printf("%s\n",buffer);
}

void find_messages(){
    char buffer[500] = "find_message ";
    char message[420];
    yellow();
    printf("please enter your message to find it : \n");
    gets(message);
    gets(message);
    strcpy(buffer + 13 , message);
    strcat(buffer , ", ");
    strcat(buffer , Token);
    strcat(buffer , "\n");
    ConnectToServer();
    send(client_socket , buffer , sizeof(buffer) , 0);
    recv(client_socket, buffer, sizeof(buffer), 0);
    cJSON *i = NULL;
    cJSON *h = cJSON_Parse(buffer);
    cJSON *content = cJSON_GetObjectItem(h, "content");
    yellow();
    printf("your saerch results : \n");
    cJSON_ArrayForEach(i, content) {
        if (strcmp(cJSON_GetObjectItem(i, "sender") -> valuestring, "server")) {
            yellow();
            printf("sender : ");
            yellow();
            printf("%s ", cJSON_GetObjectItem(i, "sender") -> valuestring);
            yellow();
            printf("full message : ");
            yellow();
            printf("%s\n", cJSON_GetObjectItem(i, "content") -> valuestring);
        }
    }
}
void ConnectToServer() {
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return;
    }
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    if (connect(client_socket, (SA *) &servaddr, sizeof(servaddr)) != 0) {
        exit(0);
    }
}