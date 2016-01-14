.PHONY : all test clean

GCC			= gcc
CFLAGS		= -Wall -ansi -pedantic -I. -std=c99
LDFLAGS		= -lm
GLIB_FLAGS	= `pkg-config --cflags glib-2.0`
GLIB_LIB	= `pkg-config --libs glib-2.0`
GPP			= g++
CPPFLAGS	= -Wall -ansi -pedantic -I. -std=c++11
GTEST_FLAGS	= -isystem gtest/include -pthread
#GTEST_LIB	= gtest/gtest_main_mac.a
GTEST_LIB	= gtest/gtest_main.a

MEM_PATH							= mem/mem
NUM_PATH							= num/num
LIST_ITEM_PATH						= adt/list/list_item/list_item
LIST_PATH							= adt/list/list/list
STR_PATH							= str/str
CG_PATH								= cg/cg
COLLISION_PATH						= cg/collision/collision
CGPP_PATH							= cgpp/cgpp
STRPP_PATH							= strpp/strpp
D2W_PATH							= d2w/d2w
ADDRESS_PATH						= net/address/address
MESSAGE_PATH						= net/message/message
SOCK_PATH							= net/sock/sock
CONNECTION_PATH						= net/connection/connection
SERVER_CONNECTION_PATH				= net/server/server_connection/server_connection
SERVER_PATH							= net/server/server/server
CLIENT_CONNECTION_PATH				= net/client/client_connection/client_connection
CLIENT_PATH							= net/client/client/client
NETWORK_PATH						= net/network/network

CHEADERS	= $(MEM_PATH).h \
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

CFILES		= $(MEM_PATH).c \
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

CPPHEADERS	= $(MEM_PATH).h \
			  $(NUM_PATH).h \
			  $(LIST_ITEM_PATH).h \
			  $(LIST_PATH).h \
			  $(STR_PATH).h \
			  $(CG_PATH).h \
			  $(COLLISION_PATH).h \
			  $(CGPP_PATH).h \
			  $(STRPP_PATH).h \
			  $(D2W_PATH).h \

CPPFILES	= $(MEM_PATH).c \
			  $(NUM_PATH).c \
			  $(LIST_ITEM_PATH).c \
			  $(LIST_PATH).c \
			  $(STR_PATH).c \
			  $(CG_PATH).c \
			  $(COLLISION_PATH).c \
			  $(CGPP_PATH).cpp \
			  $(STRPP_PATH).cpp \
			  $(D2W_PATH).cpp \

TESTS		= $(MEM_PATH)_test \
			  $(NUM_PATH)_test \
			  $(LIST_ITEM_PATH)_test \
			  $(LIST_PATH)_test \
			  $(STR_PATH)_test \
			  $(CG_PATH)_test \
			  $(COLLISION_PATH)_test \
			  $(CGPP_PATH)_test \
			  $(STRPP_PATH)_test \
			  $(D2W_PATH)_test \
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

$(MEM_PATH)_test: $(MEM_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(NUM_PATH)_test: $(NUM_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(LIST_ITEM_PATH)_test: $(LIST_ITEM_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(LIST_PATH)_test: $(LIST_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(STR_PATH)_test: $(STR_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(CG_PATH)_test: $(CG_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(COLLISION_PATH)_test: $(COLLISION_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(CGPP_PATH)_test: $(CGPP_PATH)_test.cpp $(CPPFILES) $(CPPHEADERS)
	$(GPP) $(CPPFLAGS) $(GTEST_FLAGS) -o $@ $< $(CPPFILES) $(GTEST_LIB) $(LDFLAGS)

$(STRPP_PATH)_test: $(STRPP_PATH)_test.cpp $(STRPPFILES) $(STRPPHEADERS)
	$(GPP) $(CPPFLAGS) $(GTEST_FLAGS) -o $@ $< $(CPPFILES) $(GTEST_LIB) $(LDFLAGS)

$(D2W_PATH)_test: $(D2W_PATH)_test.cpp $(CPPFILES) $(CPPHEADERS)
	$(GPP) $(CPPFLAGS) $(GTEST_FLAGS) -o $@ $< $(CPPFILES) $(GTEST_LIB) $(LDFLAGS)

$(ADDRESS_PATH)_test: $(ADDRESS_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(MESSAGE_PATH)_test: $(MESSAGE_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(SOCK_PATH)_test: $(SOCK_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(CONNECTION_PATH)_test: $(CONNECTION_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(SERVER_CONNECTION_PATH)_test: $(SERVER_CONNECTION_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(SERVER_PATH)_test: $(SERVER_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(CLIENT_CONNECTION_PATH)_test: $(CLIENT_CONNECTION_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(CLIENT_PATH)_test: $(CLIENT_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)

$(NETWORK_PATH)_test: $(NETWORK_PATH)_test.c $(CFILES) $(CHEADERS)
	$(GCC) $(CFLAGS) $(GLIB_FLAGS) -o $@ $< $(CFILES) $(GLIB_LIB) $(LDFLAGS)
