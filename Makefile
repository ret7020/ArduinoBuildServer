CC = /bin/gcc
CLIENT_NAME = absClient
SERVER_NAME = absServer
SERVER_SOURCES = server.c
CLIENT_SOURCES = client.c

all:
	$(CC) -O3 -o $(SERVER_NAME) $(SERVER_SOURCES)
	$(CC) -O3 -o $(CLIENT_NAME) $(CLIENT_SOURCES)

clean:
	rm $(NAME)

clean_ws:
	rm -r tmp && mkdir tmp