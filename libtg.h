#include <curl/curl.h>
#include <json-c/json.h>
#include <stdbool.h>

#ifndef _H_LIBTG
#define _H_LIBTG

typedef struct Buffer {
    char *data;
    size_t size;
} tg_Buffer;

typedef struct tg_Message tg_Message;
typedef struct tg_Messages tg_Messages;
typedef struct tg_Chat tg_Chat;
typedef struct tg_StaticBehaviour tg_StaticBehaviour;
typedef struct tg_ReactionType tg_ReactionType;
typedef struct tg_ReactionTypeEmoji tg_ReactionTypeEmoji;
typedef struct tg_ReactionTypeCustomEmoji tg_ReactionTypeCustomEmoji;
typedef struct tg_ChatPhoto tg_ChatPhoto;
typedef struct tg_User tg_User;
typedef struct tg_ChatPermissions tg_ChatPermissions;
typedef struct tg_ChatLocation tg_ChatLocation;
typedef struct tg_Location tg_Location;
typedef struct tg_MessageOrigin tg_MessageOrigin;
typedef struct tg_ExternalReplyInfo tg_ExternalReplyInfo;
typedef struct tg_TextQuote tg_TextQuote;
typedef struct tg_MessageEntity tg_MessageEntity;
typedef struct tg_Story tg_Story;
typedef struct tg_LinkPreviewOptions tg_LinkPreviewOptions;
typedef struct tg_PhotoSize tg_PhotoSize;
typedef struct tg_Animation tg_Animation;
typedef struct tg_Audio tg_Audio;
typedef struct tg_Document tg_Document;
typedef struct tg_Sticker tg_Sticker;
typedef struct tg_Video tg_Video;
typedef struct tg_VideoNote tg_VideoNote;
typedef struct tg_Voice tg_Voice;
typedef struct tg_MessageEntity tg_MessageEntity;
typedef struct tg_Contact tg_Contact;
typedef struct tg_Dice tg_Dice;
typedef struct tg_Game tg_Game;
typedef struct tg_Poll tg_Poll;
typedef struct tg_Venue tg_Venue;
typedef struct tg_Audio tg_Audio;
typedef struct tg_MessageAutoDeleteTimerChanged tg_MessageAutoDeleteTimerChanged;
typedef struct tg_InaccessibleMessage tg_InaccessibleMessage;
typedef struct tg_MaybeInaccessibleMessage tg_MaybeInaccessibleMessage;
typedef struct tg_Invoice tg_Invoice;
typedef struct tg_SuccessfulPayment tg_SuccessfulPayment;
typedef struct tg_UsersShared tg_UsersShared;
typedef struct tg_ChatShared tg_ChatShared;
typedef struct tg_PollOption tg_PollOption;
typedef struct tg_ShippingAdress tg_ShippingAdress;
typedef struct tg_OrderInfo tg_OrderInfo;
typedef struct tg_WriteAccessAllowed tg_WriteAccessAllowed;
typedef struct tg_PassportData tg_PassportData;
typedef struct tg_ForumTopicCreated tg_ForumTopicCreated;
typedef struct tg_ForumTopicEdited tg_ForumTopicEdited;
typedef struct tg_ForumTopicClosed tg_ForumTopicClosed;
typedef struct tg_ForumTopicReopened tg_ForumTopicReopened;
typedef struct tg_GeneralForumTopicHidden tg_GeneralForumTopicHidden;
typedef struct tg_GeneralForumTopicUnhidden tg_GeneralForumTopicUnhidden;
typedef struct tg_Giveaway tg_Giveaway;
typedef struct tg_GiveawayCreated tg_GiveawayCreated;
typedef struct tg_GiveawayWinners tg_GiveawayWinners;
typedef struct tg_GiveawayCompleted tg_GiveawayCompleted;
typedef struct tg_VideoChatScheduled tg_VideoChatScheduled;
typedef struct tg_VideoChatStarted tg_VideoChatStarted;
typedef struct tg_VideoChatEnded tg_VideoChatEnded;
typedef struct tg_VideoChatParticipantsInvited tg_VideoChatParticipantsInvited;
typedef struct tg_WebAppData tg_WebAppData;
typedef struct tg_WebAppInfo tg_WebAppInfo;
typedef struct tg_LoginUrl tg_LoginUrl;
typedef struct tg_SwitchInlineQueryChosenChat tg_SwitchInlineQueryChosenChat;
typedef struct tg_CallbackGame tg_CallbackGame;
typedef struct tg_InlineKeyboardButton tg_InlineKeyboardButton;
typedef struct tg_InlineKeyboardMarkup tg_InlineKeyboardMarkup;
typedef struct tg_ProximityAlertTriggered tg_ProximityAlertTriggered;
typedef struct tg_ChatBoostAdded tg_ChatBoostAdded;
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */
/* typedef struct tg_ tg_; */

struct tg_User{
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
};

struct tg_MessageOrigin{
    void *a; // TODO: finish
};

struct tg_ExternalReplyInfo{
    void *a; // TODO: finish
};

struct tg_TextQuote{
    char *text;
    tg_MessageEntity *entities;
    int64_t position;
    bool is_manual;
};

struct tg_Location{
    float latitude;
    float longitude;
    float horizontal_accuracy;
    int64_t live_period;
    int64_t heading;
    int64_t proximity_alert_radius;
};

struct tg_ChatLocation{
    tg_Location location;
    char *address;
};

struct tg_ChatPhoto{
    char *small_file_id;
    char *small_file_unique_id;
    char *big_file_id;
    char *big_file_unique_id;
};

struct tg_ReactionTypeEmoji{
    char *type; // Type of the reaction, always "emoji"
    char *emoji;
};

struct tg_ReactionTypeCustomEmoji{
    char *type; // Type of the reaction, always "custom_emoji"
    char *custom_emoji_id;
};

struct tg_ChatPermissions{
    bool can_send_messages;
    bool can_send_audios;
    bool can_send_documents;
    bool can_send_photos;
    bool can_send_videos;
    bool can_send_video_notes;
    bool can_send_voice_notes;
    bool can_send_polls;
    bool can_send_other_messages;
    bool can_add_web_page_previews;
    bool can_change_info;
    bool can_invite_users;
    bool can_pin_messages;
    bool can_manage_topics;
};

struct tg_ReactionType{
    union {
        tg_ReactionTypeEmoji emoji;
        tg_ReactionTypeCustomEmoji custom_emoji;
    };
};

struct tg_Chat{
    int64_t id;
    char *type;
    char *title; // Optional
    char *username; // Optional
    char *first_name; // Optional
    char *last_name; // Optional
    bool is_forum; // Optional
    tg_ChatPhoto photo; // Optional
    char ** active_usernames; // Optional
    tg_ReactionType *available_reactions; // Optional
    int64_t accent_color_id; // Optional
    char *background_custom_emoji_id; // Optional
    int64_t profile_accent_color_id; // Optional
    char *profile_background_custom_emoji_id; // Optional
    char *emoji_status_custom_emoji_id; // Optional
    char *emoji_status_expiration_date; // Optional
    char *bio; // Optional
    bool has_private_forwards; // Optional
    bool has_restricted_voice_and_video_messages; // Optional
    bool join_to_send_messages; // Optional
    bool join_by_request; // Optional
    char *description; // Optional
    char *invite_link; // Optional
    tg_Message *pinned_message; // Optional
    tg_ChatPermissions permissions; // Optional
    int64_t slow_mode_delay; // Optional
    int64_t unrestrict_boost_count; // Optional
    int64_t message_auto_delete_time; // Optional
    bool has_aggressive_anti_spam_enabled; // Optional
    bool has_hidden_members; // Optional
    bool has_protected_content; // Optional
    bool has_visible_history; // Optional
    char *sticker_set_name; // Optional
    bool can_set_sticker_set; // Optional
    char *custom_emoji_sticker_set_name; // Optional
    int64_t linked_chat_id; // Optional
    tg_ChatLocation location; // Optional
};

struct tg_Story{
    tg_Chat chat;
    int64_t id;
};

struct tg_LinkPreviewOptions{
    bool is_disabled;
    char *url;
    bool prefer_small_media;
    bool prefer_large_media;
    bool show_above_text;
};

struct tg_PhotoSize{
    char *file_id;
    char *file_unique_id;
    int64_t width;
    int64_t height;
    int64_t file_size; // Optional
};

struct tg_Animation{
    char *file_id;
    char *file_unique_id;
    int64_t width;
    int64_t height;
    int64_t duration;
    tg_PhotoSize thumbnail;
    char *file_name;
    char *mime_type;
    int64_t file_size;
};
struct tg_Document{
    char *file_id;
    char *file_unique_id;
    tg_PhotoSize thumbnail;
    char *file_name;
    char *mime_type;
    int64_t file_size;
};
struct tg_Sticker{
    char *file_id;
    char *file_unique_id;
    char *type;
    int64_t width;
    int64_t height;
    bool is_animated;
    bool is_video;
    tg_PhotoSize thumbnail; // Optional
    char *emoji; // Optional
    char *set_name; // Optional
    // TODO: tg_File premium_animation; // Optional
    // TODO: tg_MaskPosition mask_position; // Optional
    char *custom_emoji_id; // Optional
    bool needs_repainting; // Optional
    int64_t file_size; // Optional
};
struct tg_Video{
    char *file_id;
    char *file_unique_id;
    int64_t width;
    int64_t height;
    int64_t duration;
    tg_PhotoSize thumbnail;
    char *file_name;
    char *mime_type;
    int64_t file_size;
};
struct tg_VideoNote{
    char *file_id;
    char *file_unique_id;
    int64_t lehgth; // diameter of circle
    int64_t duration;
    tg_PhotoSize thumbnail;
    int64_t file_size;
};
struct tg_Voice{
    char *file_id;
    char *file_unique_id;
    int64_t duration;
    tg_PhotoSize thumbnail;
    char *mime_type;
    int64_t file_size;
};
struct tg_MessageEntity{
    char *type;
    int64_t offset;
    int64_t length;
    char *url;
    tg_User user;
    char *language;
    char *custom_emoji_id;
};
struct tg_Contact{
    char *phone_number;
    char *first_name;
    char *last_name;
    int64_t user_id;
    char *vcard;
};
struct tg_Dice{
    char *emoji;
    int64_t integer;
};
struct tg_Game{
    char *title;
    char *description;
    tg_PhotoSize photo;
    char *text;
    tg_MessageEntity text_entities;
    tg_Animation animation;
};
struct tg_PollOption{
    char *text;
    int64_t voter_count;
};
struct tg_Poll{
    char *id;
    char *question;
    tg_PollOption *options;
    int64_t total_voter_count;
    bool is_closed;
    bool is_anonymous;
    char *type;
    bool allows_multiple_answers;
    int64_t correct_option_id;
    char *explanation;
    tg_MessageEntity *explanation_entities;
    int64_t open_period;
    int64_t close_date;
};
struct tg_Venue{
    tg_Location location;
    char *title;
    char *address;
    char *foursquare_id;
    char *foursquare_type;
    char *google_place_id;
    char *google_place_type;
};
struct tg_Audio{
    char *file_id;
    char *file_unique_id;
    int64_t duration;
    char *performer;
    char *title;
    char *file_name;
    char *mime_type;
    int64_t file_size;
    tg_PhotoSize thumbnail;
};
struct tg_MessageAutoDeleteTimerChanged{
    int64_t message_auto_delete_time;
};
struct tg_InaccessibleMessage{
    tg_Chat chat;
    int64_t messageid;
    int64_t date;
};
struct tg_MaybeInaccessibleMessage{
    union{
        tg_Message *message;
        tg_InaccessibleMessage inaccessible_message;
    };
};
struct tg_Invoice{
    char *title;
    char *description;
    char *start_parameter;
    char *currency;
    int64_t total_amount;
};
struct tg_ShippingAdress{
    char *country_code;
    char *state;
    char *city;
    char *street_line1;
    char *street_line2;
    char *post_code;
};
struct tg_OrderInfo{
    char *name;
    char *phone_number;
    char *email;
    tg_ShippingAdress shipping_address;
};
struct tg_SuccessfulPayment{
    char *currency;
    int64_t total_amount;
    char *invoice_payload;
    char *shipping_option_id;
    tg_OrderInfo order_info;
    char *telegram_payment_charge_id;
    char *provider_payment_charge_id;
};
struct tg_UsersShared{
    int64_t request_id;
    int64_t *user_ids;
};
struct tg_ChatShared{
    int64_t request_id;
    int64_t chat_id;
};
struct tg_ProximityAlertTriggered{
    tg_UsersShared traveler;
    tg_User watcher;
    int64_t distance;
};
struct tg_ChatBoostAdded{
    int64_t boost_count;
};
struct tg_WriteAccessAllowed{
    bool from_request;
    char *web_app_name;
    bool from_attachment_menu;
};
struct tg_PassportData{
    void *a; // TODO: fix
    /* tg_EncryptedPassportElement *data; */
    /* credentials *EncryptedCredentials; */
};
struct tg_ForumTopicCreated{
    char *name;
    int64_t icon_color;
    char *icon_custom_emoji_id;
};
struct tg_ForumTopicEdited{
    char *name;
    char *icon_custom_emoji_id;
};
struct tg_ForumTopicClosed{
    bool closed;
};
struct tg_ForumTopicReopened{
    bool reopened;
};
struct tg_GeneralForumTopicHidden{
    bool hidden;
};
struct tg_GeneralForumTopicUnhidden{
    bool unhidden;
};
struct tg_Giveaway{
    tg_Chat *chats;
    int64_t winners_selection_date;
    int64_t winner_count;
    bool only_new_members;
    bool has_public_winners;
    char *prize_description;
    char **country_codes;
    int64_t premium_subscription_month_count;
};
struct tg_GiveawayCreated{
    bool created;
};
struct tg_GiveawayWinners{
    tg_Chat chat;
    int64_t giveaway_message_id;
    int64_t winners_selection_date;
    int64_t winner_count;
    tg_User *winners;
    int64_t additional_chat_count;
    int64_t premium_subscription_month_count;
    int64_t unclaimed_prize_count;
    bool only_new_members;
    bool was_refunded;
    char *prize_description;
};
struct tg_GiveawayCompleted{
    int64_t winner_count;
    int64_t unclaimed_prize_count;
    tg_Message *giveaway_message;
};
struct tg_VideoChatScheduled{
    int64_t start_date;
};
struct tg_VideoChatStarted{
    bool started;
};
struct tg_VideoChatEnded{
    int64_t duration;
};
struct tg_VideoChatParticipantsInvited{
    tg_User *users;
};
struct tg_WebAppData{
    char *data;
    char *button_text;
};
struct tg_WebAppInfo{
    char *url;
};
struct tg_LoginUrl{
    char *url;
    char *forward_text;
    char *bot_username;
    bool request_write_access;
};
struct tg_SwitchInlineQueryChosenChat{
    char *query;
    bool allow_user_chats;
    bool allow_bot_chats;
    bool allow_group_chats;
    bool allow_channel_chats;
};
struct tg_CallbackGame{
    void *placeHolder; // INFO: do not use
};
struct tg_InlineKeyboardButton{
    char *text;
    char *url;
    char *callback_data;
    tg_WebAppInfo web_app;
    tg_LoginUrl login_url;
    char *switch_inline_query;
    char *switch_inline_query_current_chat;
    tg_SwitchInlineQueryChosenChat switch_inline_query_chosen_chat;
    tg_CallbackGame callback_game;
    bool pay;
};
struct tg_InlineKeyboardMarkup{
    tg_InlineKeyboardButton **inline_keyboard;
};
struct tg_Message {
    int64_t message_id;
    int64_t date;
    tg_Chat chat;
    int64_t message_thread_id; // Optional
    tg_User from; // Optional
    tg_Chat sender_chat; // Optional
    int64_t sender_boost_count; // Optional
    tg_MessageOrigin forward_origin; // Optional
    bool is_topic_message; // Optional
    bool is_automatic_forward; // Optional
    struct tg_Message *reply_to_message; // Optional
    tg_ExternalReplyInfo external_reply; // Optional
    tg_TextQuote quote; // Optional
    tg_Story reply_to_story; // Optional
    tg_User via_bot; // Optional
    int64_t edit_date; // Optional
    bool has_protected_content; // Optional
    char *media_group_id; // Optional
    char *author_signature; // Optional
    char *text; // Optional
    tg_MessageEntity *entities; // Optional
    tg_LinkPreviewOptions *link_preview_options; // Optional
    tg_Animation animation; // Optional
    tg_Audio audio; // Optional
    tg_Document document; // Optional
    tg_PhotoSize photo; // Optional
    tg_Sticker sticker; // Optional
    tg_Story story; // Optional
    tg_Video video; // Optional
    tg_VideoNote video_note; // Optional
    tg_Voice voice; // Optional
    char *caption; // Optional
    tg_MessageEntity caption_entities; // Optional
    bool has_media_spoiler; // Optional
    tg_Contact contact; // Optional
    tg_Dice dice; // Optional
    tg_Game game; // Optional
    tg_Poll poll; // Optional
    tg_Venue venue; // Optional
    tg_Location location; // Optional
    tg_User *new_chat_members; // Optional
    tg_User left_chat_member; // Optional
    char *new_chat_title; // Optional
    tg_PhotoSize *new_chat_photo; // Optional
    bool delete_chat_photo; // Optional
    bool group_chat_created; // Optional
    bool supergroup_chat_created; // Optional
    bool channel_chat_created; // Optional
    tg_MessageAutoDeleteTimerChanged message_auto_delete_timer_changed; // Optional
    int64_t migrate_to_chat_id; // Optional
    int64_t migrate_from_chat_id; // Optional
    tg_MaybeInaccessibleMessage pinned_message; // Optional
    tg_Invoice invoice; // Optional
    tg_SuccessfulPayment successful_payment; // Optional
    tg_UsersShared users_shared; // Optional
    tg_UsersShared chat_shared; // Optional
    char *connected_website; // Optional
    tg_WriteAccessAllowed write_access_allowed; // Optional
    tg_PassportData passport_data; // Optional
    tg_ProximityAlertTriggered proximity_alert_triggered; // Optional
    tg_ChatBoostAdded boost_added; // Optional
    tg_ForumTopicCreated forum_topic_created; // Optional
    tg_ForumTopicEdited forum_topic_edited; // Optional
    tg_ForumTopicClosed forum_topic_closed; // Optional
    tg_ForumTopicReopened forum_topic_reopened; // Optional
    tg_GeneralForumTopicHidden general_forum_topic_hidden; // Optional
    tg_GeneralForumTopicUnhidden general_forum_topic_unhidden; // Optional
    tg_GiveawayCreated giveaway_created; // Optional
    tg_Giveaway giveaway; // Optional
    tg_GiveawayWinners giveaway_winners; // Optional
    tg_GiveawayCompleted  giveaway_completed; // Optional
    tg_VideoChatScheduled video_chat_scheduled; // Optional
    tg_VideoChatStarted video_chat_started; // Optional
    tg_VideoChatEnded video_chat_ended; // Optional
    tg_VideoChatParticipantsInvited video_chat_participants_invited; // Optional
    tg_WebAppData web_app_data; // Optional
    tg_InlineKeyboardMarkup reply_markup; // Optional
};


struct tg_Messages{
    tg_Message *msg;
    int count;
};

struct tg_StaticBehaviour{
    char *command;
    char*(*func)(void);
};


typedef struct tg_Message tg_Message;
typedef struct tg_Messages tg_Messages;
typedef struct tg_Chat tg_Chat;
typedef struct tg_StaticBehaviour tg_StaticBehaviour;
typedef struct tg_ReactionType tg_ReactionType;
typedef struct tg_ChatPhoto tg_ChatPhoto;
typedef struct tg_User tg_User;

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
