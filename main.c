#include "9cc.h"

// エラーを報告するための関数
// printfと同じ引数を取る
void error(char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}

//エラーメッセージの改良

void error_at(char *loc, char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	int pos = loc - user_input;
	fprintf(stderr, "%s\n", user_input);
	fprintf(stderr, "%*s", pos, " ");//pos個の空白を出力
	fprintf(stderr, "^");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	exit(1);
}


int main(int argc, char **argv) {
	if (argc != 2)
		error("引数の数が正しくありません");

	// トークナイズする
	user_input = argv[1];
	token = tokenize();
	Node *node = expr();

	// アセンブリの前半部分を出力
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

	// 抽象構文木を下りながらコード生成
	gen(node);

	// スタックトップに敷き全体の値が残っているはずなので
	// それをRAXにロードしてから関数からの返り値とする
	printf("	pop rax\n");
	printf("	ret\n");
	return 0;
}

