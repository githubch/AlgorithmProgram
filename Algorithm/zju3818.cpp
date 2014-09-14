#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

bool IsMeetConstrainOfSchemaOfABABA(int lenOfStr, int lenOfA, int lenOfB)
{
	return lenOfA % 2 == lenOfStr % 2 && (lenOfStr - 3 * lenOfA) % 2 == 0 && (lenOfB = (lenOfStr - 3 * lenOfA) / 2) >= 1;
}

bool IsStringEqual(char *str1, char *str2, int len)
{
	int inc = 0;
	while(inc < len && str1[inc] == str2[inc]) inc++;
	return inc < len ? false : true;
}

bool IsMeetSchemeOfABABA(char *str, int lenOfA, int lenOfB)
{
	return IsStringEqual(str, str + lenOfA + lenOfB, lenOfA) &&
		IsStringEqual(str, str + (lenOfA + lenOfB) * 2, lenOfA) &&
		IsStringEqual(str + lenOfA, str + 2 * lenOfA + lenOfB, lenOfB) &&
		!(lenOfA == lenOfB &&IsStringEqual(str, str + lenOfA, lenOfA));
}

int IsSchemaOfABABA(char * str){
	if(str == NULL || strlen(str) < 4)
		return false;
	int lenOfStr = strlen(str);
	int lenOfA = 1;
	int lenOfB = 1;
	for(lenOfA = 1; lenOfA < lenOfStr / 2; lenOfA++)
	{
		if(IsMeetConstrainOfSchemaOfABABA(lenOfStr, lenOfA, lenOfB = (lenOfStr - 3 * lenOfA) / 2))
		{
			if(IsMeetSchemeOfABABA(str, lenOfA, lenOfB))
				return true;
		}
	}
	return false;
}

bool IsMeetConstrainOfSchemaOfABABCAB(int lenOfStr, int lenOfAB, int lenOfC)
{
	return lenOfC % 3 == lenOfStr % 3 && (lenOfStr - lenOfC) % 3 == 0 && (lenOfAB = (lenOfStr - lenOfC) / 3) >= 2;
}

bool IsSameAmongABC(char * str, int lenOfA, int lenOfB, int lenOfC)
{
	return lenOfA == lenOfB && IsStringEqual(str, str + lenOfA, lenOfA) ||
		lenOfA == lenOfC && IsStringEqual(str, str + (lenOfA + lenOfB) * 2, lenOfA) || 
		lenOfB == lenOfC && IsStringEqual(str + lenOfA, str + (lenOfA + lenOfB) * 2, lenOfB);
}

bool IsMeetSchemeOfABABCAB(char *str, int lenOfAB, int lenOfC)
{
	return IsStringEqual(str, str + lenOfAB, lenOfAB) && IsStringEqual(str, str + lenOfAB * 2 + lenOfC, lenOfAB);
}

int IsSchemaOfABABCAB(char * str){
	if(str == NULL || strlen(str) < 6)
		return false;
	int lenOfStr = strlen(str);
	int lenOfC = 1;
	int mod3OfStr = lenOfStr % 3;
	int lenOfAB = 1;
	int lenOfA = 1;
	int lenOfB = 1;
	for(lenOfC = 1; lenOfC <= lenOfStr - 6; lenOfC ++)
	{
		if(IsMeetConstrainOfSchemaOfABABCAB(lenOfStr, lenOfAB = (lenOfStr - lenOfC) / 3, lenOfC))
		{
			if(!IsMeetSchemeOfABABCAB(str, lenOfAB, lenOfC)) continue;

			for(lenOfA = 1; lenOfA < lenOfAB;lenOfA++)
			{
				lenOfB = lenOfAB - lenOfA;
				if(!IsSameAmongABC(str, lenOfA, lenOfB, lenOfC))
					return true;
			}
		}
	}
	return false;
}

void SpiltPunc(char *src, char *dest)
{
	if(src == NULL || dest == NULL)
		return;
	int inc = 0;
	int lenOfSrc = strlen(src);
	int indexOfDest = 0;;
	while(inc < lenOfSrc)
	{
		if(isalpha(src[inc]))
		{
			dest[indexOfDest++] = src[inc];
		}
		inc++;
	}
	dest[indexOfDest] = '\0';
}

int main()
{
	const int LEN_MAX = 55;
	int T = 0;
	scanf("%d%*c", &T);
	char str[LEN_MAX]={'\0'};
	char strOfNoPunc[LEN_MAX] = {'\0'};
	int lineOfInput = 0;
	while(lineOfInput < T)
	{
		scanf("%s", str);
		
		SpiltPunc(str, strOfNoPunc);
		if(IsSchemaOfABABA(strOfNoPunc) || IsSchemaOfABABCAB(strOfNoPunc))
			printf("Yes\n");
		else
			printf("No\n");
		lineOfInput++;
	}
}