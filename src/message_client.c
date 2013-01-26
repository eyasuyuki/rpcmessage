#include <stdio.h>
#include "msg.h"			/* rpcgen が生成した msg.h */

main(int argc, char **argv) {
	CLIENT *clnt;
	int *result;
	char *server;
	char *message;

	if (argc != 3) {
		fprintf(stderr, "usage: %s host message\n", argv[0]);
		return 1;
	}

	server = argv[1];
	message = argv[2];
	/*
	 * コマンド行で指定したサーバの
	 * MESSAGEPROG の呼び出しで使用する
	 * クライアント「ハンドル」を作成
	 */
	clnt = clnt_create(server, MESSAGEPROG, PRINTMESSAGEVERS, "tcp");
	if (clnt == (CLIENT *) NULL ) {
		/*
		 * サーバーとの接続確立に失敗したため、
		 * エラーメッセージを表示して終了
		 */
		clnt_pcreateerror(server);
		return 1;
	}
	/*
	 * サーバー上のリモートプロシージャ printmessage を
	 * 呼び出す
	 */
	result = printmessage_1(&message, clnt);
	if (result == (int *) NULL ) {
		/*
		 * サーバーの呼び出しでエラーが発生したため、
		 * エラーメッセージを表示して終了
		 */
		clnt_perror(clnt, server);
		return 1;
	}
	/*
	 *  リモートプロシージャ呼び出しは正常終了
	 */
	if (*result == 0) {
		/*
		 * サーバーがメッセージの表示に失敗したため、
		 * エラーメッセージを表示して終了
		 */
		fprintf(stderr, "%s: could not print your message\n", argv[0]);
		return 1;
	}
	/* サーバーのコンソールにメッセージが出力された
	 */
	printf("Message delivered to %s\n", server);
	clnt_destroy(clnt);

	return 0;
}
