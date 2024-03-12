#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "libtg.h"

#define IF_COMMAND(a, msg) if(strcmp(a, msg.text)==0)

char *HelpCommand(void){
    return "This%20bot%20can%20do%20stuff.";
}

char *PingCommand(void){
    return "Pong!";
}
int count = 0;
char countcommandstr[10];
char *CountCommand(void){
    count++;
    sprintf(countcommandstr, "count:%d.", count);
    puts(countcommandstr);
    return countcommandstr;
}

int main(void) {
    FILE *token_file = fopen("token.txt", "r");
    fseek(token_file, 0, SEEK_END);
    long fsize = ftell(token_file);
    fseek(token_file, 0, SEEK_SET);
    char *token = malloc(fsize+1);
    fread(token, fsize, 1, token_file);
    token[fsize-1]=0;//replace '\n' that is put before EOF due to UNIX :(
    tg_InitBot(token);
    tg_AddStaticBehaviour("/help",  HelpCommand);
    tg_AddStaticBehaviour("/ping",  PingCommand);
    tg_AddStaticBehaviour("/count", CountCommand);
    while(1){
        tg_Messages messages = tg_GetMessages();
        printf("msg count = %d\n", messages.count);
        for(int i=0; i<messages.count; i++){
            tg_Message msg = messages.msg[i];
            switch(msg.type){
                case MSG_UNKNOWN:
                    continue;
                case MSG_TEXT:
                    tg_ReplyStatic(msg);
                    break;
                case MSG_STICKER:
                    printf("sticker = '%s'\n",   msg.text);
                    break;
                case MSG_PHOTO:
                    printf("photo sent.\n");
                    break;
                default: break;
            }
            tg_FreeMessage(&msg);
        }
    }
    tg_StopBot();
    return 0;
}
