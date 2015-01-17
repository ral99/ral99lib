.PHONY : all test

CFLAGS		= -Wall -ansi -pedantic -I. -std=c99
GLIB_FLAGS	= `pkg-config --cflags glib-2.0`
GLIB_LIB	= `pkg-config --libs glib-2.0`

UTIL_PATH							= util/util
NUM_PATH							= num/num
LIST_ITEM_PATH						= adt/list/list_item/list_item
LIST_PATH							= adt/list/list/list
STR_PATH							= adt/str/str
ADDRESS_PATH						= net/address/address
MESSAGE_PATH						= net/message/message
SOCK_PATH							= net/sock/sock
CONNECTION_PATH						= net/connection/connection
SERVER_CONNECTION_PATH				= net/server/server_connection/server_connection
SERVER_PATH							= net/server/server/server
CLIENT_CONNECTION_PATH				= net/client/client_connection/client_connection
CLIENT_PATH							= net/client/client/client
NETWORK_PATH						= net/network/network

HEADERS		= $(UTIL_PATH).h \
			  $(NUM_PATH).h \
			  $(LIST_ITEM_PATH).h \
			  $(LIST_PATH).h \
			  $(STR_PATH).h \
			  $(ADDRESS_PATH).h \
			  $(MESSAGE_PATH).h \
			  $(SOCK_PATH).h \
			  $(CONNECTION_PATH).h \
			  $(SERVER_CONNECTION_PATH).h \
			  $(SERVER_PATH).h \
			  $(CLIENT_CONNECTION_PATH).h \
			  $(CLIENT_PATH).h \
			  $(NETWORK_PATH).h \

FILES		= $(UTIL_PATH).c \
			  $(NUM_PATH).c \
			  $(LIST_ITEM_PATH).c \
			  $(LIST_PATH).c \
			  $(STR_PATH).c \
			  $(ADDRESS_PATH).c \
			  $(MESSAGE_PATH).c \
			  $(SOCK_PATH).c \
			  $(CONNECTION_PATH).c \
			  $(SERVER_CONNECTION_PATH).c \
			  $(SERVER_PATH).c \
			  $(CLIENT_CONNECTION_PATH).c \
			  $(CLIENT_PATH).c \
			  $(NETWORK_PATH).c \

TESTS		= $(UTIL_PATH)_test \
			  $(NUM_PATH)_test \
			  $(LIST_ITEM_PATH)_test \
			  $(LIST_PATH)_test \
			  $(STR_PATH)_test \
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

$(UTIL_PATH)_test: $(UTIL_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(NUM_PATH)_test: $(NUM_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(LIST_ITEM_PATH)_test: $(LIST_ITEM_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(LIST_PATH)_test: $(LIST_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(STR_PATH)_test: $(STR_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(ADDRESS_PATH)_test: $(ADDRESS_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(MESSAGE_PATH)_test: $(MESSAGE_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(SOCK_PATH)_test: $(SOCK_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(CONNECTION_PATH)_test: $(CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(SERVER_CONNECTION_PATH)_test: $(SERVER_CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(SERVER_PATH)_test: $(SERVER_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(CLIENT_CONNECTION_PATH)_test: $(CLIENT_CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(CLIENT_PATH)_test: $(CLIENT_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)

$(NETWORK_PATH)_test: $(NETWORK_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB)
