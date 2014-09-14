#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

int IsSchemaOfABABA(char * str){
	if(str == NULL || strlen(str) < 4)
		return false;
	int lenOfStr = strlen(str);
	int lenOfA = 1;
	int lenOfB = 1;
	int mod2OfStr = lenOfStr % 2;
	for(lenOfA = 1; lenOfA < lenOfStr / 2; lenOfA++)
	{
		//should meet the constrains about the relationship among lenOfA, lenOfB, lenOfStr
		if(lenOfA % 2 == mod2OfStr && (lenOfStr - 3 * lenOfA) % 2 == 0 && (lenOfB = (lenOfStr - 3 * lenOfA) / 2) >= 1)
		{
			int lenOfAB = lenOfA + lenOfB;

			int inc = 0;
			while(inc < lenOfA && str[inc] == str[lenOfAB + inc]) inc++;
			if(inc < lenOfA) continue;

			inc = 0;
			while(inc < lenOfA && str[inc] == str[lenOfAB * 2 + inc]) inc++;
			if(inc < lenOfA) continue;

			inc = 0;
			while(inc < lenOfB && str[lenOfA + inc] == str[2 * lenOfA + lenOfB + inc]) inc++;
			if(inc < lenOfB) continue;

			//A and B should not be same
			if(lenOfA == lenOfB){
				inc = 0;
				while(inc < lenOfA && str[inc] == str[inc + lenOfA])inc++;
				if(inc == lenOfA)
					continue;
			}

			return true;
		}
	}
	return false;
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
		//should meet the constrains of schema of ABABCAB
		if(lenOfC % 3 == mod3OfStr && (lenOfStr - lenOfC) % 3 == 0 && (lenOfAB = (lenOfStr - lenOfC) / 3) >= 2)
		{
			int inc = 0;
			while(inc < lenOfAB && str[inc] == str[lenOfAB + inc]) inc++;
			if(inc < lenOfAB) continue;

			inc = 0;
			while(inc < lenOfAB && str[inc] == str[lenOfAB * 2 + lenOfC + inc]) inc++;
			if(inc < lenOfAB) continue;
			

			for(lenOfA = 1; lenOfA < lenOfAB;lenOfA++)
			{
				lenOfB = lenOfAB - lenOfA;
				if(lenOfA == lenOfB)
				{
					inc = 0;
					while(inc < lenOfA && str[inc] == str[lenOfA + inc]) inc++;
					if(inc == lenOfA) continue;
				}

				if(lenOfA == lenOfC)
				{
					inc = 0;
					while(inc < lenOfA && str[inc] == str[lenOfAB * 2 + inc]) inc++;
					if(inc == lenOfA) continue;
				}

				if(lenOfB == lenOfC)
				{
					inc = 0;
					while(inc < lenOfB && str[lenOfA + inc] == str[lenOfAB * 2 + inc]) inc++;
					if(inc == lenOfB) continue;
				}
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