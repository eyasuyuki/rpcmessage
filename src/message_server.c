#include <stdio.h>
#include "msg.h"				/* msg.h  rpcgen が生成 */

int *printmessage_1_svc(char **msg, struct svc_req *req) {
	static int result; /* 必ず static で宣言 */
	FILE *f;

	f = fopen("/dev/console", "w");
//	f = fopen("/dev/tty", "w");
	if (f == (FILE *) NULL ) {
		result = 0;
		return (&result);
	}
	fprintf(f, "%s\n", *msg);
	fclose(f);
	result = 1;
	return (&result);
}
