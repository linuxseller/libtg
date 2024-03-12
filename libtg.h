#include <curl/curl.h>
#include <json-c/json.h>
#include <stdbool.h>

#ifndef _H_LIBTG
#define _H_LIBTG

typedef struct Buffer {
    char *data;
    size_t size;
} tg_Buffer;

enum tg_MessageType {
    MSG_TEXT,
    MSG_STICKER,
    MSG_ANIMATION,
    MSG_AUDIO,
    MSG_DOCUMENT,
    MSG_PHOTO,
    MSG_STORY,
    MSG_VIDEO,
    MSG_VIDEO_NOTE,
    MSG_VOICE,
    MSG_UNKNOWN
};

typedef struct {
    int64_t id;
    bool is_bot;
    char *first_name;
    char *last_name;
    char *username;
    char *language_code;
    bool is_premium;
    bool added_to_attachment_menu;
    bool can_join_groups;
    bool can_read_all_group_messages;
    bool supports_inline_requests;
} tg_User;

typedef struct {
    int64_t id;
    char *type;
    char *title;
    char *username;
    char *first_name;
    char *last_name;
    bool is_forum;
    tg_ChatPhoto photo;
    char ** active_usernames;
    tg_ReactionType available_reactions;
    int64_t accent_color_id;
    char *background_custom_emoji_id;
    int64_t profile_accent_color_id;
    char *profile_background_custom_emoji_id;
    char *emoji_status_custom_emoji_id;
    char *emoji_status_expiration_date;
    char *bio;
    bool has_private_forwards;
    bool has_restricted_voice_and_video_messages;
    bool join_to_send_messages;
    bool join_by_request;
    char *description;
    char *invite_link;
    tg_Message pinned_message;
    tg_ChatPermissions permissions;
    int64_t invite_link;
    int64_t unrestrict_boost_count;
    int64_t message_auto_delete_time
    bool has_aggressive_anti_spam_enabled;
    bool has_hidden_members;
    bool has_protected_content;
    bool has_visible_history;
    char *sticker_set_name;
    bool can_set_sticker_set;
    char *custom_emoji_sticker_set_name;
    int64_t linked_chat_id;
    tg_ChatLocation location;
} tg_Chat;

typedef struct tg_Message {
    int64_t message_id;
    int64_t message_thread_id;
    tg_User from;
    tg_Chat sender_chat;
    int64_t sender_boost_count;
    int64_t date;
    tg_Chat chat;
    tg_MessageOrigin forward_origin;
    bool is_topic_message;
    bool is_automatic_forward;
    struct tg_Message reply_to_message;
    tg_ExternalReplyInfo external_reply;
    tg_TextQuote quote;
    tg_Story reply_to_story;
    tg_User via_bot;
    int64_t edit_date;
// TODO: finish 
    enum tg_MessageType type;
    union {
        char *text;
        char *sticker;
    };
} tg_Message;

typedef struct {
    tg_Message *msg;
    int count;
} tg_Messages;

typedef struct {
    char *command;
    char*(*func)(void);
} tg_StaticBehaviour;

bool tg_IsStaticBehaviour(tg_Message msg);
void tg_AddStaticBehaviour(char *command, char*(*func)(void));
void tg_ReplyStatic(tg_Message msg);
void tg_SsendMessage(const char *message, u_int64_t chat_id);
tg_Messages tg_GetMessages(void);
void updateLastTelegramMessage(const char *message);
size_t tg_MessageBufferer(void *contents, size_t size, size_t nmemb, void *userdata);
void tg_FreeMessage(tg_Message *msg);
void tg_SendMessage(const char *message, u_int64_t chat_id);
int tg_InitBot(const char *token);
void tg_StopBot(void);



#endif
