#ifndef __NET__MESSAGE__
#define __NET__MESSAGE__

typedef struct Message *Message;
struct Message {
    char *id;
    char *text;
};

/* Return a new message. */
Message message_new(char *id, char *text);

/* Free the memory used by message. */
void message_release(Message message);

/* Return 1 if messages are equal. 0, otherwise. */
int message_equals(Message message1, Message message2);

/* Return the string representation of the message. */
char *message_to_str(Message message);

/* Return message from its string representation. */
Message message_from_str(char *str);

/* Return the duplicated message. */
Message message_dup(Message message);

/* Getter method for id. */
char *message_get_id(Message message);

/* Setter method for id. */
void message_set_id(Message message, char *id);

/* Getter method for text. */
char *message_get_text(Message message);

/* Setter method for text. */
void message_set_text(Message message, char *text);

/* Boolean method for id. */
int message_id_is(Message message, char *id);

/* Boolean method for text. */
int message_text_is(Message message, char *text);

/* Return the id of the connection that received the message. */
char *message_id(Message message);

/* Return the message text. */
char *message_text(Message message);

#endif

