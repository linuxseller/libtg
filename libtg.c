#include <json-c/json.h>
#include <curl/curl.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include "libtg.h"
CURL *tg_curl;
tg_Buffer tg_buffer;
char *tg_token;
unsigned int tg_last_update_id;

#define JOBJ_GET_INT(jobj, str) (json_object_get_int(json_object_object_get(jobj, str)))
#define JOBJ_GET_STR(jobj, str) (json_object_get_string(json_object_object_get(jobj, str)))
#define JOBJ_GET_BOOL(jobj, str) (json_object_get_boolean(json_object_object_get(jobj, str)))

#define SET_STR_IF_EXISTS(val, jobj, str) { \
    struct json_object* tmp = json_object_object_get(jobj, str); \
    if(tmp){ \
        val = strdup(JOBJ_GET_STR(jobj, str)); \
    } \
}
#define SET_INT_IF_EXISTS(val, jobj, str) { \
    struct json_object* tmp = json_object_object_get(jobj, str); \
    if(tmp){ \
        val = JOBJ_GET_INT(jobj, str); \
    } \
}
#define SET_BOOL_IF_EXISTS(val, jobj, str) { \
    struct json_object* tmp = json_object_object_get(jobj, str); \
    if(tmp){ \
        val = JOBJ_GET_BOOL(jobj, str); \
    } \
}
int tg_InitBot(const char *token)
{
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
    // TODO: finish
    free(msg->from.username);
    free(msg->text);
}

tg_PhotoSize _tg_ParsePhotoSize(struct json_object *jobj_photo_size)
{
    // I have no idea why that guys from telegram called it photo size when it is just photo.
    // Its my code and I do what I wanna do, were balling
    tg_PhotoSize photo = {0};
    photo.file_id = strdup(JOBJ_GET_STR(jobj_photo_size, "file_id"));
    photo.file_unique_id = strdup(JOBJ_GET_STR(jobj_photo_size, "file_unique_id"));
    photo.width = JOBJ_GET_INT(jobj_photo_size, "width");
    photo.height = JOBJ_GET_INT(jobj_photo_size, "height");
    photo.file_size = JOBJ_GET_INT(jobj_photo_size, "file_size");
    return photo;
}

tg_Sticker _tg_ParseSticker(json_object *jobj_sticker)
{
    tg_Sticker sticker = {0};
    sticker.file_id = strdup(JOBJ_GET_STR(jobj_sticker, "file_id"));
    sticker.file_unique_id = strdup(JOBJ_GET_STR(jobj_sticker, "file_unique_id"));
    sticker.type = strdup(JOBJ_GET_STR(jobj_sticker, "type"));
    sticker.width = JOBJ_GET_INT(jobj_sticker, "width");
    sticker.height = JOBJ_GET_INT(jobj_sticker, "height");
    sticker.is_animated = JOBJ_GET_BOOL(jobj_sticker, "is_animated");
    sticker.is_video = JOBJ_GET_BOOL(jobj_sticker, "is_video");
    sticker.thumbnail = _tg_ParsePhotoSize(json_object_object_get(jobj_sticker, "thumbnail"));
    SET_STR_IF_EXISTS(sticker.emoji, jobj_sticker, "emoji");
    SET_STR_IF_EXISTS(sticker.set_name, jobj_sticker, "set_name");
    SET_STR_IF_EXISTS(sticker.custom_emoji_id, jobj_sticker, "custom_emoji_id");
    SET_BOOL_IF_EXISTS(sticker.needs_repainting, jobj_sticker, "needs_repainting");
    SET_INT_IF_EXISTS(sticker.file_size, jobj_sticker, "file_size");
    return sticker;
}
tg_Chat _tg_ParseChat(struct json_object *jobj_chat){
    tg_Chat chat = {0};
    chat.id = JOBJ_GET_INT(jobj_chat, "id");
    chat.type = strdup(JOBJ_GET_STR(jobj_chat, "type"));
    SET_STR_IF_EXISTS(chat.title, jobj_chat, "title");
    SET_STR_IF_EXISTS(chat.username, jobj_chat, "username");
    SET_STR_IF_EXISTS(chat.first_name, jobj_chat, "first_name");
    SET_STR_IF_EXISTS(chat.last_name, jobj_chat, "last_name");
    SET_BOOL_IF_EXISTS(chat.is_forum, jobj_chat, "is_forum");
    // chat.photo = _tg_ParseChatPhoto(jobj_chat);
    // chat.active_usernames = _tg_ParseActiveUsernames();
    // chat.available_reactions = _tg_ParseReactionTypes();
    SET_INT_IF_EXISTS(chat.accent_color_id, jobj_chat, "accent_color_id");
    SET_STR_IF_EXISTS(chat.background_custom_emoji_id, jobj_chat, "background_custom_emoji_id");
    SET__IF_EXISTS(chat., jobj_chat, "");
    //TODO: finish
    return chat;
}
tg_Message _tg_ParseMessage(struct json_object *jobj_message_container){
    tg_Message msg = {0};
    struct json_object *jobj_message = json_object_object_get(jobj_message_container, "message");
    struct json_object *jobj_chat    = json_object_object_get(jobj_message, "chat");
    // type = text
    SET_STR_IF_EXISTS(msg.text, jobj_message, "text");
    struct json_object *jobj_message_sticker = json_object_object_get(jobj_message, "sticker");
    if(jobj_message_sticker){
        msg.sticker = _tg_ParseSticker(jobj_message_sticker);
    }
    msg.message_id = JOBJ_GET_INT(jobj_message, "message_id");
    msg.date = JOBJ_GET_INT(jobj_message_container, "date");
    msg.chat = _tg_ParseChat(json_object_object_get(jobj_message, "chat"));
    msg.chat.type = strdup(JOBJ_GET_STR(jobj_chat, "type"));
    return msg;
}

tg_Messages tg_GetMessages(void)
{
    CURLcode res;
    tg_Messages msgs = {.msg = NULL, .count=0};
    char *url = malloc(512*sizeof(char));
    sprintf(url, "https://api.telegram.org/bot%s/getUpdates?offset=%d", tg_token, tg_last_update_id+1);
    curl_easy_setopt(tg_curl, CURLOPT_URL, url);
    res = curl_easy_perform(tg_curl);
    if (res != CURLE_OK)
        fprintf(stderr, "tg_GetMessages: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    struct json_object *jobj_root = json_tokener_parse(tg_buffer.data);
    struct json_object *jobj_result = json_object_object_get(jobj_root, "result");
    int messages_count = json_object_array_length(jobj_result);
    msgs.msg = malloc(sizeof(tg_Message)*messages_count);
    msgs.count = messages_count;
    for (int i = 0; i < messages_count; i++) {
        struct json_object *jobj_message_container = json_object_array_get_idx(jobj_result, i);
        msgs.msg[i] = _tg_ParseMessage(jobj_message_container);
        tg_last_update_id = JOBJ_GET_INT(jobj_message_container, "update_id");
    }
    free(url);
    return msgs;
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
