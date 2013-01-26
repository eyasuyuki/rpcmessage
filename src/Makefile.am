bin_PROGRAMS=messageServer messageClient

EXTRA_DIST = msg.x

msg_GEN = msg.h msg_svc.c msg_clnt.c
CLEANFILES = $(msg_GEN) msg_stamp
$(msg_GEN) : msg_stamp
msg_stamp : msg.x
	rpcgen msg.x
	touch $@

messageServer_SOURCES=msg_svc.c message_server.c

messageClient_SOURCES=msg_clnt.c message_client.c
