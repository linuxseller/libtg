#include <json-c/json.h>
#include <curl/curl.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

#include "libtg.h"
CURL *tg_curl;
tg_Buffer tg_buffer;
char *tg_token;
unsigned int tg_last_update_id;
int tg_sbs_count = 1;
tg_StaticBehaviour *tg_sbs;

void tg_AddStaticBehaviour(char *command, char*(*func)(void))
{
    tg_sbs[tg_sbs_count-1] = (tg_StaticBehaviour){
        .command = strdup(command),
        .func = func
    };
    tg_sbs_count++;
    tg_sbs = realloc(tg_sbs, sizeof(tg_StaticBehaviour)*tg_sbs_count);
}

void tg_ReplyStatic(tg_Message msg)
{
    for (int i = 0; i < tg_sbs_count-1; i++) {
        if(strcmp(tg_sbs[i].command, msg.text)==0){
            tg_SendMessage(tg_sbs[i].func(), msg.chat_id);
            return;
        }
    }
    tg_SendMessage("Unknown Command", msg.chat_id);
}

bool tg_IsStaticBehaviour(tg_Message msg)
{
    for (int i = 0; i < tg_sbs_count-1; i++) {
        if(strcmp(tg_sbs[i].command, msg.text)==0){
            return true;
        }
    }
    return false;
}
int tg_InitBot(const char *token)
{
    tg_sbs = malloc(sizeof(tg_StaticBehaviour));
    tg_last_update_id = 0;
    tg_token = strdup(token);
    curl_global_init(CURL_GLOBAL_DEFAULT);
    tg_curl = curl_easy_init();
    curl_easy_setopt(tg_curl, CURLOPT_WRITEFUNCTION, tg_MessageBufferer);
    curl_easy_setopt(tg_curl, CURLOPT_WRITEDATA, (void *)&tg_buffer);
    curl_easy_setopt(tg_curl, CURLOPT_TIMEOUT, 60L);
    if (!tg_curl) {
        return -1;
    }
    return 0;
}
void tg_StopBot(void)
{
    free(tg_token);
    curl_easy_cleanup(tg_curl);
    curl_global_cleanup();
}
void tg_FreeMessage(tg_Message *msg)
{
    free(msg->username);
    free(msg->text);
}
tg_Messages tg_GetMessages(void)
{
    CURLcode res;
    tg_Messages msg = {.msg = NULL, .count=0};
    char *url = malloc(512*sizeof(char));
    sprintf(url, "https://api.telegram.org/bot%s/getUpdates?offset=%d", tg_token, tg_last_update_id+1);
    curl_easy_setopt(tg_curl, CURLOPT_URL, url);
    res = curl_easy_perform(tg_curl);
    if (res != CURLE_OK)
        fprintf(stderr, "tg_GetMessages: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    struct json_object *jobj_root = json_tokener_parse(tg_buffer.data);
    struct json_object *jobj_result = json_object_object_get(jobj_root, "result");
    int messages_count = json_object_array_length(jobj_result);
    msg.msg = malloc(sizeof(tg_Message)*messages_count);
    msg.count = messages_count;
    for (int i = 0; i < messages_count; i++) {
        struct json_object *jobj_message_container = json_object_array_get_idx(jobj_result, i);
        struct json_object *jobj_message      = json_object_object_get(jobj_message_container, "message");
        struct json_object *jobj_message_id   = json_object_object_get(jobj_message_container, "message_id");
        struct json_object *jobj_update_id    = json_object_object_get(jobj_message_container, "update_id");
        struct json_object *jobj_chat_id      = json_object_object_get(
                                                            json_object_object_get(jobj_message, "chat"), "id");
        struct json_object *jobj_from         = json_object_object_get(jobj_message, "from");
        struct json_object *jobj_user_nick    = json_object_object_get(jobj_from, "username");
        // Getting mesage type
        struct json_object *jobj_message_text = json_object_object_get(jobj_message, "text");
        struct json_object *jobj_message_sticker = json_object_object_get(jobj_message, "sticker");
        struct json_object *jobj_message_animation  = json_object_object_get(jobj_message, "animation");
        struct json_object *jobj_message_audio      = json_object_object_get(jobj_message, "audio");
        struct json_object *jobj_message_document   = json_object_object_get(jobj_message, "document");
        struct json_object *jobj_message_photo      = json_object_object_get(jobj_message, "photo");
        struct json_object *jobj_message_story      = json_object_object_get(jobj_message, "story");
        struct json_object *jobj_message_video      = json_object_object_get(jobj_message, "video");
        struct json_object *jobj_message_video_note = json_object_object_get(jobj_message, "video_note");
        struct json_object *jobj_message_voice     = json_object_object_get(jobj_message, "");
        if(jobj_message_text){
            if(jobj_user_nick){
                msg.msg[i].username = strdup(json_object_get_string(jobj_user_nick));
            }
            msg.msg[i].type     = MSG_TEXT;
            msg.msg[i].text     = strdup(json_object_get_string(jobj_message_text));
        } else if(jobj_message_sticker){
            msg.msg[i].type = MSG_STICKER;
            struct json_object *jobj_message_sticker_emoji = json_object_object_get(jobj_message_sticker, "emoji");
            msg.msg[i].sticker = strdup(json_object_get_string(jobj_message_sticker_emoji));
            msg.msg[i].username   = strdup(json_object_get_string(jobj_user_nick));
        } else if (jobj_message_animation){
            msg.msg[i].type = MSG_ANIMATION;
        } else if (jobj_message_audio){
            msg.msg[i].type = MSG_AUDIO;
        } else if (jobj_message_document){
            msg.msg[i].type = MSG_DOCUMENT;
        } else if (jobj_message_photo){
            msg.msg[i].type = MSG_PHOTO;
        } else if (jobj_message_story){
            msg.msg[i].type = MSG_STORY;
        } else if (jobj_message_video){
            msg.msg[i].type = MSG_VIDEO;
        } else if (jobj_message_video_note){
            msg.msg[i].type = MSG_VIDEO_NOTE;
        } else if (jobj_message_voice){
            msg.msg[i].type = MSG_VOICE;
        } else {
            msg.msg[i].type = MSG_UNKNOWN;
        }

        msg.msg[i].message_id = json_object_get_int64(jobj_message_id);
        msg.msg[i].chat_id    = json_object_get_int64(jobj_chat_id);
        // last update id update
        tg_last_update_id = json_object_get_int(jobj_update_id);
    }
    free(url);
    return msg;
}

void tg_SendMessage(const char *message, u_int64_t chat_id)
{
    (void)message;
    CURLcode res;
    char url[256];
    snprintf(url, sizeof(url), "https://api.telegram.org/bot%s/sendMessage?chat_id=%"PRId64"&text=%s",
             tg_token, chat_id, message);
    curl_easy_setopt(tg_curl, CURLOPT_URL, url);
    res = curl_easy_perform(tg_curl);
    if (res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
}
size_t tg_MessageBufferer(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Buffer *mem = (struct Buffer *)userp;
    if(mem->data==NULL){
        mem->data=malloc((realsize+1)*sizeof(char));
    } else if (mem->size<realsize){
        mem->data=realloc(mem->data, (realsize+1)*sizeof(char));
        if(mem->data==NULL){
            exit(EXIT_FAILURE);
        }
    }
    memcpy(mem->data, contents, realsize);
    mem->size = realsize;
    mem->data[mem->size] = 0;  // Null-terminate the string
    return realsize;
}
