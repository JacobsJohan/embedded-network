#include "stdlib.h"
#include "string.h"

#include "zmq_connection.h"

/************************** Private functions **************************/
static float my_strtof(char *nptr) {
        float f = 0.0;
        while ((*nptr >= '0') && (*nptr <= '9')) {
                f = (f * 10.0) + (*nptr++ - '0');
        }

        if (*nptr == '.') {
                float cv = 1.0;
                nptr++;
                while ((*nptr >= '0') && (*nptr <= '9')) {
                        cv *= 0.1;
                        f = f + (cv*(*nptr++ - '0'));
                }
        }

        return f;
}

/************************** Public functions **************************/

/* Initialize ZMQ REQ socket on the given ip and port
 * Returns 0 on success, -1 on failure
 */
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


/* Close a socket
 * Returns 0 on success, -1 on failure
 */
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


/* Request the temperature via the presented REQ socket and saves it to temp
 * Returns 0 on success, -1 on failure
 */
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
        rx_buffer[ret] = '\0';

        *temp = my_strtof(rx_buffer);

        return 0;
}
