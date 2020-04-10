#include "stdlib.h"
#include "string.h"

#include "zmq_connection.h"

int init_req_sock(void **zctx, void **zsock, const char *ip, int port)
{
        int ret = 0;
        char endpoint[128] = "";
        void *ctx = NULL;
        void *sock = NULL;

        ctx = zmq_ctx_new();
        if (ctx == NULL) {
                perror("zmq_ctx_new");
                return -1;
        }

        sock = zmq_socket(ctx, ZMQ_REQ);
        if (sock == NULL) {
                perror("zmq_ctx_new");
                return -1;
        }

        // Connect to server
        snprintf(endpoint, 128, "tcp://%s:%d", ip, port);
        ret = zmq_connect(sock, endpoint);
        if (ret < 0) {
                perror("zmq_connect");
                return ret;
        }

        *zctx = ctx;
        *zsock = sock;
        return 0;
}

int close_sock(void *zsock)
{
        int ret = 0;
        ret = zmq_close(zsock);
        if (ret < 0) {
                perror("zmq_close");
                ret = -1;
        }

        return ret;
}

int request_temp(void *zsock, float *temp)
{
        int ret = 0;
        const int buffer_len = 128;
        char *msg_req_temp = "req/temperature";
        char rx_buffer[buffer_len];
        // Request temperature
        ret = zmq_send(zsock, msg_req_temp, strlen(msg_req_temp), 0);
        if (ret < 0) {
                perror("zmq_send");
                return -1;
        }

        // Receive temperature
        ret = zmq_recv(zsock, rx_buffer, buffer_len - 1, 0);
        if (ret < 0) {
                perror("zmq_recv");
                return -1;
        }

        *temp = strtof(rx_buffer, NULL);

        return 0;
}
