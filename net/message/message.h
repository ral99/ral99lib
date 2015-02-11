#ifndef __NET__MESSAGE__
#define __NET__MESSAGE__

typedef struct _NETMessage *NETMessage;
struct _NETMessage {
    char *id;
    char *text;
};

/* Return a new message. */
NETMessage message_new(char *id, char *text);

/* Free the memory used by message. */
void message_release(NETMessage message);

/* Return 1 if messages are equal. 0, otherwise. */
int message_equals(NETMessage message1, NETMessage message2);

/* Return the string representation of the message. */
char *message_to_str(NETMessage message);

/* Return message from its string representation. */
NETMessage message_from_str(char *str);

/* Return the duplicated message. */
NETMessage message_dup(NETMessage message);

/* Getter method for id. */
char *message_get_id(NETMessage message);

/* Setter method for id. */
void message_set_id(NETMessage message, char *id);

/* Getter method for text. */
char *message_get_text(NETMessage message);

/* Setter method for text. */
void message_set_text(NETMessage message, char *text);

/* Boolean method for id. */
int message_id_is(NETMessage message, char *id);

/* Boolean method for text. */
int message_text_is(NETMessage message, char *text);

/* Return the id of the connection that received the message. */
char *message_id(NETMessage message);

/* Return the message text. */
char *message_text(NETMessage message);

#endif

