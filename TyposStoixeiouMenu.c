/*Kωνσταντίνος Στεφανίδης-Βοζίκης Α.Μ.:1115201400192*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TyposStoixeiouMenu.h"

void TSSetValue(TStoixeiouMenu *Lhs, TStoixeiouMenu Rhs)
{
	strcpy(Lhs->name, Rhs.name);
	Lhs->Category=Rhs.Category;
	Lhs->Price=Rhs.Category;
}

int TSReadValue(FILE *in, TStoixeiouMenu *V)
{
	char ch;
	int size, position=0;
	printf("Patiste 0 gia eisagogi piatou i 1 gia eisagogi katigorias\n");
	fscanf(in, "%d", &(V->Category));
	if (V->Category==0)
	printf("Doste to onoma tou piatou\n");
	else printf("Doste to onoma tis katigorias\n");
	size=15;
	V->name=malloc(15*sizeof(char));
		if(V->name==NULL)
		return 0;
	fscanf(in, "%c", &ch);
	while(isspace(ch))
	fscanf(in, "%c", &ch);
	do
	{
		V->name[position++]=ch;
		if(position+1==size)
		{
			realloc(V->name, ++size);
			if(V->name==NULL)
				return 0;
		}
		fscanf(in, "%c", &ch);
	}while(!(ch=='\n'));
	V->name[position]='\0';
	if (V->Category==0)
	{
		printf("Doste tin timi tou piatou\n");
		fscanf(in, "%f", &(V->Price));
		return 1;
	}
	else
	return 2;
}

int TSPrintValue(FILE *out, TStoixeiouMenu V)
{
	fprintf(out, "%s", V.name);
	if (V.Category==0)
	fprintf(out, ": %.1f$", V.Price);
}

int TSReadAgainValue(FILE *in, TStoixeiouMenu *V)
{
	char ch;
	int size, position=0;
	size=strlen(V->name);
	if (V->Category==0)
	printf("Doste to onoma tou piatou\n");
	else printf("Doste to onoma tis katigorias\n");
	fscanf(in, "%c", &ch);
	while(isspace(ch))
	fscanf(in, "%c", &ch);
	do
	{
		V->name[position++]=ch;
		if(position+1==size)
		{
			realloc(V->name, ++size);
			if(V->name==NULL)
				return 0;
		}
		fscanf(in, "%c", &ch);
	}while(!(ch=='\n'));
	V->name[position]='\0';
	fflush(stdout);
	if (V->Category==0)
	{
		printf("Doste tin timi tou piatou\n");
		fscanf(in, "%f", &(V->Price));
	}
	return 1;
}
