.PHONY : all test clean

CC			= gcc
CFLAGS		= -Wall -ansi -pedantic -I. -std=c99
LDFLAGS		= -lm
GLIB_FLAGS	= `pkg-config --cflags glib-2.0`
GLIB_LIB	= `pkg-config --libs glib-2.0`

MEM_PATH							= mem/mem
NUM_PATH							= num/num
LIST_ITEM_PATH						= adt/list/list_item/list_item
LIST_PATH							= adt/list/list/list
STR_PATH							= str/str
CG_PATH								= cg/cg
COLLISION_PATH						= cg/collision/collision
ADDRESS_PATH						= net/address/address
MESSAGE_PATH						= net/message/message
SOCK_PATH							= net/sock/sock
CONNECTION_PATH						= net/connection/connection
SERVER_CONNECTION_PATH				= net/server/server_connection/server_connection
SERVER_PATH							= net/server/server/server
CLIENT_CONNECTION_PATH				= net/client/client_connection/client_connection
CLIENT_PATH							= net/client/client/client
NETWORK_PATH						= net/network/network

HEADERS		= $(MEM_PATH).h \
			  $(NUM_PATH).h \
			  $(LIST_ITEM_PATH).h \
			  $(LIST_PATH).h \
			  $(STR_PATH).h \
			  $(CG_PATH).h \
			  $(COLLISION_PATH).h \
			  $(ADDRESS_PATH).h \
			  $(MESSAGE_PATH).h \
			  $(SOCK_PATH).h \
			  $(CONNECTION_PATH).h \
			  $(SERVER_CONNECTION_PATH).h \
			  $(SERVER_PATH).h \
			  $(CLIENT_CONNECTION_PATH).h \
			  $(CLIENT_PATH).h \
			  $(NETWORK_PATH).h \

FILES		= $(MEM_PATH).c \
			  $(NUM_PATH).c \
			  $(LIST_ITEM_PATH).c \
			  $(LIST_PATH).c \
			  $(STR_PATH).c \
			  $(CG_PATH).c \
			  $(COLLISION_PATH).c \
			  $(ADDRESS_PATH).c \
			  $(MESSAGE_PATH).c \
			  $(SOCK_PATH).c \
			  $(CONNECTION_PATH).c \
			  $(SERVER_CONNECTION_PATH).c \
			  $(SERVER_PATH).c \
			  $(CLIENT_CONNECTION_PATH).c \
			  $(CLIENT_PATH).c \
			  $(NETWORK_PATH).c \

TESTS		= $(MEM_PATH)_test \
			  $(NUM_PATH)_test \
			  $(LIST_ITEM_PATH)_test \
			  $(LIST_PATH)_test \
			  $(STR_PATH)_test \
			  $(CG_PATH)_test \
			  $(COLLISION_PATH)_test \
			  $(ADDRESS_PATH)_test \
			  $(MESSAGE_PATH)_test \
			  $(SOCK_PATH)_test \
			  $(CONNECTION_PATH)_test \
			  $(SERVER_CONNECTION_PATH)_test \
			  $(SERVER_PATH)_test \
			  $(CLIENT_CONNECTION_PATH)_test \
			  $(CLIENT_PATH)_test \
			  $(NETWORK_PATH)_test \

all: test clean

test: $(TESTS)
	gtester $(TESTS) --keep-going

clean:
	rm $(TESTS)

$(MEM_PATH)_test: $(MEM_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(NUM_PATH)_test: $(NUM_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(LIST_ITEM_PATH)_test: $(LIST_ITEM_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(LIST_PATH)_test: $(LIST_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(STR_PATH)_test: $(STR_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(CG_PATH)_test: $(CG_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(COLLISION_PATH)_test: $(COLLISION_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(ADDRESS_PATH)_test: $(ADDRESS_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(MESSAGE_PATH)_test: $(MESSAGE_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(SOCK_PATH)_test: $(SOCK_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(CONNECTION_PATH)_test: $(CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(SERVER_CONNECTION_PATH)_test: $(SERVER_CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(SERVER_PATH)_test: $(SERVER_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(CLIENT_CONNECTION_PATH)_test: $(CLIENT_CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(CLIENT_PATH)_test: $(CLIENT_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)

$(NETWORK_PATH)_test: $(NETWORK_PATH)_test.c $(FILES) $(HEADERS)
	$(CC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(LDFLAGS)
