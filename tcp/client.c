#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <zmq.h>

/* This is the client-side code which will run on the laptop.
 * The client will connect to the server and request the current temperature.
 */
int main(void)
{
        int ret = 0;
        int ret_cleanup = 0;
        const int buffer_len = 128;
        void *zctx = NULL;
        void *zsock = NULL;
        char rx_buffer[buffer_len];
        const char *ip_addr = "tcp://raspberrypi.local:5555";
        const char *msg_req_temp = "req/temperature";

        zctx = zmq_ctx_new();
        if (zctx == NULL) {
                perror("zmq_ctx_new");
                ret = -1;
                goto exit_main;
        }

        zsock = zmq_socket(zctx, ZMQ_REQ);
        if (zsock == NULL) {
                perror("zmq_ctx_new");
                ret = -1;
                goto exit_main;
        }

        // Connect to server
        ret = zmq_connect(zsock, ip_addr);
        if (ret < 0) {
                perror("zmq_connect");
                goto exit_main;
        }

        while (1) {
                // Request temperature
                ret = zmq_send(zsock, msg_req_temp, strlen(msg_req_temp), 0);
                if (ret < 0) {
                        perror("zmq_send");
                        goto exit_main;
                }

                // Receive temperature
                ret = zmq_recv(zsock, rx_buffer, buffer_len - 1, 0);
                if (ret < 0) {
                        perror("zmq_recv");
                        goto exit_main;
                }
                rx_buffer[ret] = '\0';

                printf("%s\n", rx_buffer);

                sleep(1);
        }

exit_main:
        ret_cleanup = zmq_close(zsock);
        if (ret_cleanup < 0) {
                perror("zmq_close");
                ret = -1;
        }

        return ret;
}
