#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

/* This is the server-side code which will run on the Raspberry Pi.
 * The server will start up and wait for requests. When a request for
 * temperature data arrives, the Pi will read out the sensor and reply.
 */
int main(void)
{
        int ret = 0;
        int ret_cleanup = 0;
        const int buffer_len = 128;
        void *zctx = NULL;
        void *zsock = NULL;
        char rx_buffer[buffer_len];
        char tx_buffer[buffer_len];
        const char *ip_addr = "tcp://0.0.0.0:5555";

        zctx = zmq_ctx_new();
        if (zctx == NULL) {
                perror("zmq_ctx_new");
                ret = -1;
                goto exit_main;
        }

        zsock = zmq_socket(zctx, ZMQ_REP);
        if (zsock == NULL) {
                perror("zmq_ctx_new");
                ret = -1;
                goto exit_main;
        }

        ret = zmq_bind(zsock, ip_addr);
        if (ret < 0) {
                perror("zmq_bind");
                goto exit_main;
        }

        while (1) {
                // Receive a request from a client
                ret = zmq_recv(zsock, rx_buffer, buffer_len - 1, 0);
                if (ret < 0) {
                        perror("zmq_recv");
                        goto exit_main;
                }
                rx_buffer[ret] = '\0';

                // Print reply
                printf("%s\n", rx_buffer);

                // Check if the server asks for temperature
                if (strncmp(rx_buffer, "req/temperature", ret) == 0) {
                        memcpy(tx_buffer, "25", 3);
                } else {
                        memcpy(tx_buffer, "Unknown request", 16);
                }

                // Send reply
                ret = zmq_send(zsock, tx_buffer, strlen(tx_buffer), 0);
                if (ret < 0) {
                        perror("zmq_send");
                        goto exit_main;
                }

                // Clear tx_buffer
                memset(tx_buffer, 0, sizeof(tx_buffer));
        }

exit_main:
        ret_cleanup = zmq_close(zsock);
        if (ret_cleanup < 0) {
                perror("zmq_close");
                ret = -1;
        }

        return ret;
}

