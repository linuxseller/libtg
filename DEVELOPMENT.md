# BIG PILE OF WORK MUST BE DONE!

## How to create structs for tg api?
easily:
```c
typedef struct {
    int64_t id;               // All 'Integer's must be int64_t
    char *type;               // All strings must be 'char *'
    bool is_forum;            // all 'True' MUST be bool
    tg_ChatPhoto photo;       // all tg api types must be 'tg_' prefixed
    char ** active_usernames; // I dunno what to do about string arrays, or other arrays now :sadge:
...
} tg_Chat;

```
