#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	TK_RESERVED, // 記号
	TK_IDENT,   // 識別子
	TK_NUM,      // 整数トークン
	TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

struct Token {
	TokenKind kind; // トークンの型
	Token *next;    // 次の入力トークン
	int val;        // kindがTK_NUMの場合、その数値
	char *str;      // トークン文字列
	int len;        // トークンの長さ
};

Token *token;

void error(char *fmt, ...);

char *user_input;

void error_at(char *loc, char *fmt, ...);

bool consume(char *op);

void expect(char *op);

int expect_number();

bool at_eof();

Token *new_token(TokenKind kind, Token *cur, char *str, int len);

bool startswith(char *p, char *q);

Token *tokenize();

typedef enum {
	ND_ADD, // +
	ND_SUB, // -
	ND_MUL, // *
	ND_DIV, // /
	ND_EQ,  // ==
	ND_NE,  // !=
	ND_LT,  // <
	ND_LE,  // <=
	ND_LVAR,// ローカル変数
	ND_NUM, // 整数
}	NodeKind;

typedef struct Node Node;

struct Node {
	NodeKind kind; // ノードの型
	Node *lhs;     // 左辺
	Node *rhs;     // 右辺
	int val;       // kindがND_NUMの場合のみ使う
	int offset;    // kindがND_LVARの場合のみ使う
};
	
Node *new_node(NodeKind kind);

Node *new_binary(NodeKind kind, Node *lhs, Node *rhs);

Node *new_num(int val);

Node *stmt();
Node *assign();
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

void gen(Node *node);
