#define _CRT_SECURE_NO_DEPRECATE
#include "source.h"

int main(int argc, char** argv) 
{
	//Load in file
	if (argv[1] != NULL)
	{
		Source = fopen(argv[1], "rb");
	}
	else
	{
		printf("ERROR: No file found at %s\n", argv[1]);
	}
	fseek(Source, 0, SEEK_END);
	fsize = ftell(Source);
	FileBuf = malloc(fsize+32);
	for (int x = 0; x < 32; x++)
	{
		FileBuf[fsize + x] = 0;
	}
	fseek(Source, 0, SEEK_SET);
	if (FileBuf != 0) 
	{
		fread(FileBuf, fsize, 1, Source);
	}
	TokenList = malloc(TokenListSize * sizeof(Token));

	Lexer();
	Parser();
	Generator();
	PrintTokens();
	fclose(Source);
	free(TokenList);
	free(FileBuf);
	return 0;
}

void Lexer()
{
	int y = 0;//Current word we're building
	while (y < fsize)
	{
		if (!isspace(FileBuf[y]))
		{
			int keyword = FindKeyword(FileBuf + y);
			if (keyword != -1)
			{
				int keylen = strlen(KeyLex[keyword].Ident);
				if (keyword < NonSymbol)//Must be a keyword
				{
					int extrac = FindAlphaNumeric(&FileBuf[keyword + keylen]);
					if (extrac == 0)//Keyword found!
					{
						PushToken(TOKEN_KEYWORD, keyword, y, keylen);
						y += keylen;
					}
					else //Identifier found!
					{
						PushToken(TOKEN_IDENTIFIER, keyword, y, keylen + extrac);
						y += keylen;
					}
				}
				else //Must be a symbol
				{
					PushToken(TOKEN_SYMBOL, keyword,  y, keylen);
					y += keylen;
				}
			}
			else //Non keyword found
			{
				int IdentLen = FindIdentifier(FileBuf + y);
				if (IdentLen > 0)//Found identifier
				{
					PushToken(TOKEN_IDENTIFIER, keyword, y, IdentLen);
					y += IdentLen;
				}
				else //Find Decimal
				{
					int decval = FindDecimal(FileBuf + y);
					if (decval > 0)
					{
						PushToken(TOKEN_DIGIT, keyword, y, decval);
						y += decval;
					}
					else
					{
						printf("ERROR ON CHARACTER %d\n", y);
					}
				}
			}
			Sind++;
		}
		else
		{
			y++;
		}
	}
}

//Reads the source buffer in and compares it with the current 
int FindKeyword(char* input)
{
	for (int x = 0; x < LexSize; x++)
	{
		if (memcmp(input, KeyLex[x].Ident, strlen(KeyLex[x].Ident)) == 0)
		{
			return x;
		}
	}
	return -1;
}

int IsAlphaNumeric(char input)
{
	if (input >= 'A' && input <= 'Z')
	{
		return 1;
	}
	else if (input >= 'a' && input <= 'z')
	{
		return 1;
	}
	else  if (input >= '0' && input <= '9')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int FindAlphaNumeric(char* input)
{
	int returnval = 0;
	while (IsAlphaNumeric(input[returnval]) && returnval < _I32_MAX)
	{
		returnval++;
	}
	return returnval;
}


int IsAlpha(char input)
{
	if (input >= 'A' && input <= 'Z')
	{
		return 1;
	}
	else if (input >= 'a' && input <= 'z')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Return num of chars if identifier
int FindIdentifier(char* input)
{
	if (IsAlpha(input[0])) 
	{
		return FindAlphaNumeric(&input[1]) + 1;
	}

	return 0;
}

int IsDigit(char input)
{
	if (input >= '0' && input <= '9') 
	{
		return 1;
	}
	return 0;
}

int FindDecimal(char* input)
{
	int returnval = 0;
	while (IsDigit(input[returnval]) && returnval < _I32_MAX)
	{
		returnval++;
	}
	return returnval;
}

void PushToken(int tokentype, int keyindex, int startpointer, int len)
{
	Token intoken = {tokentype, keyindex, startpointer, len};
	if (TokenListLen == TokenListSize)
	{
		TokenListSize *= 2;
		TokenList = realloc(TokenList, TokenListSize * sizeof(Token));
		if (TokenList == NULL)//We've fucked it, ran out of memory
		{
			printf("ERROR: RAN OUT OF MEMORY");
			exit(-1);
		}
	}
	TokenList[TokenListLen++] = intoken;
}

void PrintTokens()
{
	for (int x = 0; x < TokenListLen; x++)
	{
		printf("\nToken %d: \n	type %d, \n	keyindex %d, \n	startpointer %d, \n	length %d", x, TokenList[x].tokentype, TokenList[x].keyindex, TokenList[x].startpointer, TokenList[x].len);
	}
}


void Parser()
{

}

void Generator()
{

}