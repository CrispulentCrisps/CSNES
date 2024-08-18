#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TOKEN_KEYWORD		0
#define TOKEN_IDENTIFIER	1
#define TOKEN_SYMBOL		2
#define TOKEN_DIGIT			3

#define ERROR_NO_FILE_FOUND				-1
#define ERROR_OUT_OF_MEMORY				-2
#define ERROR_UNKNOWN_TOKEN_PARSED		-3

typedef enum UnionType
{
	UTypeNumConst,		//Constant number
	UTypeBinaryOp,		//Binary operations and mathematical operations
	UTypeDeclaring,		//Declaring variables
	UTypeAssignment,	//Assigning values
	UTypeWhileLoop,		//While loops
	UTypeForLoop,		//For loops
	UTypeFunction,		//Functions such as void, int, char*
} UnionType;

typedef struct {
	char* Ident;	//Keyword identifier for keyword
} Keyword;

typedef struct TreeNode TreeNode;

typedef struct TreeNode {
	UnionType NodeType;	//What type of node we're dealing with
	union NodeData		
	{
		struct NumConst		{ int Data; int BitDepth;															} NumConst;
		struct BinaryOp		{ int Data; TreeNode* Left; TreeNode* Right;										} BinaryOp;
		struct Declaration	{ char* Name; int Type;																} Declaration;
		struct Assignment	{ int Data; TreeNode* Destination; TreeNode* Origin;								} Assignment;
		struct WhileLoop	{ TreeNode* Condition; TreeNode* Execution;											} WhileLoop;
		struct ForLoop		{ TreeNode* Initialiser; TreeNode* Condition; TreeNode* Inc; TreeNode* Execution;	} ForLoop;
		struct Function		{ int Type; char* Name; TreeNode* Args; TreeNode* Execution;						} Function;
	};
} TreeNode;
 
const int LexSize = 77;
const int NonSymbol = 38;
const Keyword KeyLex[] = {
	{"main"		},
	{"func"		},
	{"ubyte"	},			//1 bytes
	{"uword"	},			//2 bytes
	{"ulong"	},			//3 bytes
	{"udword"	},			//4 bytes
	{"sbyte"	},			//1 bytes
	{"sword"	},			//2 bytes
	{"slong"	},			//3 bytes
	{"sdword"	},			//4 bytes
	{"bool"		},			//1 bit
	{"nullptr"	},
	{"true"		},			//1 bit
	{"false"	},			//1 bit
	{"if"		},
	{"else"		},
	{"while"	},
	{"for"		},
	{"switch"	},
	{"case"		},
	{"break"	},
	{"return"	},
	{"enum"		},			//byte per entry
	{"void"		},
	{"typedef"	},
	{"struct"	},
	{"union"	},
	{"typeof"	},
	{"#ifdef"	},
	{"#ifndef"	},
	{"#include"	},
	{"#define"	},
	{"#pragma"	},
	{"once"		},
	{"sizeof"	},
	{"asm"		},			//Inline assembly
	{"zp"		},			//Forces data to be put in zp, reserving $F0-$FF for DSP registers
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
	{"|="		},
	{"&="		},
	{"^="		},
	{"="		},
	{"+"		},
	{"-"		},
	{"*"		},
	{"/"		},
	{"%"		},
	{"!"		},
	{"~"		},
	{">"		},
	{"<"		},
	{"?"		},
	{":"		},
	{"."		},
	{","		},
	{";"		},
	{"$"		},
	{"\'"		},
	{"\""		},
	{"("		},
	{")"		},
	{"["		},
	{"]"		},
	{"{"		},
	{"}"		},
};

typedef struct Token{
	int tokentype;		//Type of token we're working with
	int keyindex;		//Index within the key lexicon
	int startpointer;	//point in the source code [measured in chars]
	int len;			//Length of keyword
} Token;

Token* TokenList;		//List of all keywords identified within the program
int TokenListLen = 0;	//How many tokens are inside the token list
int TokenListSize = 1;	//Amount of tokens in bytes [used for resizing the token* when overflowing]

FILE* Source;
FILE* Output;

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
void ParseFunction(Token token);
int DetermineFunctionArgs(Token* token, int pos);
void Generator();