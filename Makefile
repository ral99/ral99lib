.PHONY : all test staticlib clean

CFLAGS		= -Wall -ansi -pedantic -I. -std=c99
GLIB_FLAGS	= `pkg-config --cflags glib-2.0`
GLIB_LIB	= `pkg-config --libs glib-2.0`
MATH_LIB	= -lm

STATICLIB	= libcg.a

MEM_PATH							= mem/mem
NUM_PATH							= num/num
LIST_ITEM_PATH						= adt/list/list_item/list_item
LIST_PATH							= adt/list/list/list
STR_PATH							= str/str
ADDRESS_PATH						= net/address/address
MESSAGE_PATH						= net/message/message
SOCK_PATH							= net/sock/sock
CONNECTION_PATH						= net/connection/connection
SERVER_CONNECTION_PATH				= net/server/server_connection/server_connection
SERVER_PATH							= net/server/server/server
CLIENT_CONNECTION_PATH				= net/client/client_connection/client_connection
CLIENT_PATH							= net/client/client/client
NETWORK_PATH						= net/network/network
CG_PATH								= cg/cg

HEADERS		= $(MEM_PATH).h \
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
			  $(CG_PATH).h \

FILES		= $(MEM_PATH).c \
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
			  $(CG_PATH).c \

OBJECTS		= mem.o \
			  num.o \
			  list_item.o \
			  list.o \
			  str.o \
			  address.o \
			  message.o \
			  sock.o \
			  connection.o \
			  server_connection.o \
			  server.o \
			  client_connection.o \
			  client.o \
			  network.o \
			  cg.o \

TESTS		= $(MEM_PATH)_test \
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
			  $(CG_PATH)_test \

all: test staticlib clean

test: $(TESTS)
	gtester $(TESTS) --keep-going

staticlib: $(FILES) $(HEADERS)
	gcc $(CFLAGS) -c $(FILES)
	ar -cq $(STATICLIB) $(OBJECTS)

clean:
	rm $(TESTS) $(OBJECTS)

$(MEM_PATH)_test: $(MEM_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(NUM_PATH)_test: $(NUM_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(LIST_ITEM_PATH)_test: $(LIST_ITEM_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(LIST_PATH)_test: $(LIST_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(STR_PATH)_test: $(STR_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(ADDRESS_PATH)_test: $(ADDRESS_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(MESSAGE_PATH)_test: $(MESSAGE_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(SOCK_PATH)_test: $(SOCK_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(CONNECTION_PATH)_test: $(CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(SERVER_CONNECTION_PATH)_test: $(SERVER_CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(SERVER_PATH)_test: $(SERVER_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(CLIENT_CONNECTION_PATH)_test: $(CLIENT_CONNECTION_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(CLIENT_PATH)_test: $(CLIENT_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(NETWORK_PATH)_test: $(NETWORK_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)

$(CG_PATH)_test: $(CG_PATH)_test.c $(FILES) $(HEADERS)
	gcc $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(FILES) $(GLIB_LIB) $(MATH_LIB)
