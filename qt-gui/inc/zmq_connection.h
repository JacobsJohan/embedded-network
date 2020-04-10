#ifndef ZMQ_CONNECTION_H
#define ZMQ_CONNECTION_H

#include <zmq.h>

/* Initialize ZMQ REQ socket on the given ip and port
 * Returns 0 on success, -1 on failure
 */
int init_req_sock(void **zctx, void **zsock, const char *ip, int port);

/* Close a socket
 * Returns 0 on success, -1 on failure
 */
int close_sock(void *zsock);

/* Request the temperature via the presented REQ socket and saves it to temp
 * Returns 0 on success, -1 on failure
 */
int request_temp(void *zsock, float *temp);

#endif /* ZMQ_CONNECTION_H */
