#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "libtg.h"

#define IF_COMMAND(a, msg) if(strcmp(a, msg.text)==0)

int main(void) {
    printf("%lu\n", sizeof(tg_Message));
    FILE *token_file = fopen("token.txt", "r");
    if(!token_file){
        printf("[ERROR] bruh!\n");
        exit(1);
    }
    fseek(token_file, 0, SEEK_END);
    long fsize = ftell(token_file);
    fseek(token_file, 0, SEEK_SET);
    char *token = malloc(fsize+1);
    fread(token, fsize, 1, token_file);
    printf("BOT STARTED\n");
    token[fsize-1]=0;//replace '\n' that is put before EOF due to UNIX :(
    tg_InitBot(token);
    while(1){
        tg_Messages messages = tg_GetMessages();
        printf("msg count = %d\n", messages.count);
        for(int i=0; i<messages.count; i++){
            tg_Message msg = messages.msg[i];
            if(msg.text){
                tg_SendMessage(msg.text, msg.chat.id);
                printf("%s from %zd\n", msg.text, msg.chat.id);
            }
            if(msg.sticker.emoji){
                printf("%s\n", msg.sticker.emoji);
                printf("Sticker Info:\n");
                printf("size: %zdx%zd\n", msg.sticker.thumbnail.width, msg.sticker.thumbnail.height);
            }
            tg_FreeMessage(&msg);
        }
    }
    tg_StopBot();
    return 0;
}
