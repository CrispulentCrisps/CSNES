#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TOKEN_KEYWORD		0
#define TOKEN_IDENTIFIER	1
#define TOKEN_SYMBOL		2
#define TOKEN_DIGIT			3

typedef enum UnionType
{
	NumConst,	//Constant number
	BinaryOp,	//Binary operations and mathematical operations
	Declaration,//Declaring variables
	Assignment, //Assigning values
	WhileLoop,	//While loops
	ForLoop,	//For loops
	Function,	//Functions such as void, int, char*

} UnionType;

typedef struct Type 
{
	char* Name;		//Type name
	size_t Data;	//Data size in bytes
} Type;


typedef struct {
	char* Ident;	//Keyword identifier for keyword
} Keyword;

typedef struct TreeNode {
	UnionType NodeType;	//What type of node we're dealing with
	union NodeData
	{
		struct NumConst		{ int Data; int BitDepth;															} NumConst;
		struct BinaryOp		{ int Data; TreeNode* Left; TreeNode* Right;										} BinaryOp;
		struct Declaration	{ char* Name; int Type;																} Declaration;
		struct Assignment	{ int Data; TreeNode* Destination; TreeNode* Source;								} Assignment;
		struct WhileLoop	{ TreeNode* Condition; TreeNode* Execution;											} WhileLoop;
		struct ForLoop		{ TreeNode* Initialiser; TreeNode* Condition; TreeNode* Inc; TreeNode* Execution;	} ForLoop;
		struct Function		{ int Type; char* Name; TreeNode* Args; TreeNode* Execution;						} Function;
	};
} TreeNode;
 
const int LexSize = 0x4A;
const int NonSymbol = 0x35;
const Keyword KeyLex[0x4A] = {
	{"main"		},
	{"char"		},
	{"short"	},
	{"long"		},
	{"unsigned"	},
	{"signed"	},
	{"int"		},
	{"bool"		},
	{"true"		},
	{"false"	},
	{"nullptr"	},
	{"if"		},
	{"else"		},
	{"while"	},
	{"enum"		},
	{"void"		},
	{"typedef"	},
	{"struct"	},
	{"union"	},
	{"typeof"	},
	{"for"		},
	{"switch"	},
	{"case"		},
	{"break"	},
	{"typeof"	},
	{"return"	},
	{"ifdef"	},
	{"ifndef"	},
	{"include"	},
	{"define"	},
	{"pragma"	},
	{"once"		},
	{"extern"	},
	{"const"	},
	{"static"	},
	{"sizeof"	},
	{"asm"		},
	{"zp"		},
	{"++"		},
	{"--"		},
	{"//"		},
	{"<<"		},
	{"<="		},
	{">>"		},
	{">="		},
	{">>"		},
	{"=="		},
	{"+="		},
	{"-="		},
	{"*="		},
	{"/="		},
	{"!="		},
	{"="		},
	{">"		},
	{"<"		},
	{"?"		},
	{":"		},
	{"."		},
	{"\'"		},
	{"\""		},
	{"("		},
	{")"		},
	{"["		},
	{"]"		},
	{"{"		},
	{"}"		},
	{","		},
	{";"		},
	{"+"		},
	{"-"		},
	{"*"		},
	{"/"		},
	{"$"		},
	{"~"		},
};

typedef struct
{
	int tokentype;		//Type of token we're working with
	int keyindex;		//Index within the key lexicon
	int startpointer;	//point in the source code [measured in chars]
	int len;			//Length of keyword
} Token;

Token* TokenList;		//List of all keywords identified within the program
int TokenListLen = 0;
int TokenListSize = 128;

FILE* Source;

char* FileBuf;
long fsize = 0;
int Sind = 0;

TreeNode Root;

void Lexer();
int FindKeyword(char* input);
int FindAlphaNumeric(char* input);
int IsAlphaNumeric(char input);
int IsAlpha(char input);
int FindIdentifier(char* input);
int IsDigit(char input);
int FindDecimal(char* input);
void PushToken(int tokentype, int keyindex, int startpointer, int len);
void PrintTokens();
void Parser();
void Generator();