SRCS_CLIENT = client.c
SRCS_SERVER = server.c
CLIENT = client
SERVER = server
LDFLAGS += -lzmq

.PHONY: all
all:
	$(CC) $(SRCS_CLIENT) -o $(CLIENT) $(LDFLAGS)
	$(CC) $(SRCS_SERVER) -o $(SERVER) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(CLIENT) $(SERVER)
