/*Kωνσταντίνος Στεφανίδης-Βοζίκης Α.Μ.:1115201400192*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Menu.h"

typedef struct MenuNode *MenuNodePtr; // Ο τύπος δείκτη σε κόμβο

struct InfoMenu {
	char* 	  Name; 	   // το όνομα του εστιατορίου
	MenuNodePtr Start;	   // Δείκτης στον πρώτο κόμβο του πρώτου επιπέδου
	MenuNodePtr Current;   // Δείκτης στον τρέχοντα κόμβο
	MenuNodePtr CutToPaste;// Δείκτης στον κόμβο προς μεταφορά σε άλλη θέση
	MenuNodePtr LastNode;
};

struct MenuNode {
	MenuNodePtr Prev, Next, Up, Down;
	TStoixeiouMenu Data;
};

int MenuDimiourgia (InfoMenuPtr *pointer)
{
	char ch;
	int position=0, size;
	
	*pointer=malloc(sizeof(struct InfoMenu));
	if (pointer==NULL)
		return 0;
	(*pointer)->Start=malloc(sizeof(struct MenuNode));
	(*pointer)->Current=(*pointer)->Start;
	(*pointer)->Current->Up=NULL;
	(*pointer)->Current->Down=NULL;			//Αρχικοποίηση της κεφαλής
	(*pointer)->Current->Next=NULL;
	(*pointer)->Current->Prev=NULL;
	(*pointer)->LastNode=(*pointer)->Current;
	(*pointer)->CutToPaste=NULL;
	printf("Doste to onoma tis epixeirisis\n");
	(*pointer)->Name=malloc(15*sizeof(char));
	if((*pointer)->Name==NULL)
		return 0;
	size=15;
	ch=getchar();
	while(isspace(ch))
	ch=getchar();
	do
	{
		(*pointer)->Name[position++]=ch;
		if(position+1==size)
		{
			realloc((*pointer)->Name, ++size);
			if((*pointer)->Name==NULL)
				return 0;
		}
		ch=getchar();
	}while(!(ch=='\n'));
	(*pointer)->Name[position]='\0';
	return 1;
}

void PrintBusinessName(InfoMenuPtr MenuPtr)
{
	printf("To onoma tis epixeirisis einai: %s\n", MenuPtr->Name);
}
	
int MenuKeniKatigoria (InfoMenuPtr MenuPtr)
{
	if (MenuPtr->Start->Next==NULL)
	 return 0;
	return 1;
}

int MenuEisagogiKomvou (InfoMenuPtr MenuPtr)
{
	char ch;
	int res;
	MenuNodePtr temp;
	temp=malloc(sizeof(struct MenuNode));
	res=TSReadValue(stdin, &temp->Data);
	if (res==0) return 0;
	if (res==2)
	{
		temp->Down=malloc(sizeof(struct MenuNode));
		temp->Down->Down=temp->Down->Prev=temp->Down->Next=NULL;
		temp->Down->Up=temp;
	}
	else
		temp->Down=NULL;
	temp->Up=MenuPtr->Current->Up;
	temp->Next=MenuPtr->Current->Next;
	temp->Prev=MenuPtr->Current;
	MenuPtr->Current->Next=temp;
	MenuPtr->Current=temp;
	if(MenuPtr->Current->Next!=NULL)
		MenuPtr->Current->Next->Prev=temp;	//Καλύπτει την περίπτωση του τελευταίου κόμβου
	MenuPtr->LastNode=MenuPtr->Current;
	return 1;	
}

int MenuEktuposiKomvou(InfoMenuPtr MenuPtr)
{
	if(MenuPtr->Current->Prev==NULL) //Kefales
		return 0;
	TSPrintValue (stdout, MenuPtr->Current->Data);
	printf("\n");
	return 1;
}

int MenuAllagiPeriexomenou (InfoMenuPtr MenuPtr)
{
	char ch;
	if(!TSReadAgainValue(stdin, &MenuPtr->Current->Data))
		return 0;
	return 1;
}

int MenuEpomenos (InfoMenuPtr *pointer)
{
	if((*pointer)->Current->Next==NULL) 
		return 0;
	(*pointer)->Current=(*pointer)->Current->Next;
	return 1;
}
	
int MenuProigoumenos(InfoMenuPtr *pointer)
{
	if((*pointer)->Current->Prev==NULL) 
		return 0; //kefali
	(*pointer)->Current=(*pointer)->Current->Prev;
	return 1;
}
	
int MenuPano (InfoMenuPtr *pointer)
{
	if((*pointer)->Current->Up==NULL)
		return 0; /*proto epipedo*/
	(*pointer)->Current=(*pointer)->Current->Up;
	return 1;
}

int MenuKato (InfoMenuPtr *pointer)
{
	if((*pointer)->Current->Down==NULL)
		return 0; /*teleutaio epipedo*/
	(*pointer)->Current=(*pointer)->Current->Down;
	return 1;
}

/*Boithiktiki sunartisi gia na ulopoiithei i anadromi*/
/******************************************************************************************************************/
void RecEktuposi (InfoMenuPtr MenuPtr, MenuNodePtr NodePtr, int tabs, int GuideMode, int bonus, FILE *fp)
{
	int i;
	MenuNodePtr temp;
	temp=NodePtr;
	if(NodePtr->Data.Category==0)
	{
		if(GuideMode==1)
		{
			if(NodePtr->Prev->Prev==NULL && MenuPtr->Current==NodePtr->Prev) /*o current einai se kefali*/
			{
				for (i=0; i<tabs; i++)
					printf("\t");
				printf("|Head|<- You are here");
				printf("\n");
			}
		}
		for (i=0; i<tabs; i++)
			fprintf(fp, "\t");
		if (bonus==1)
			fprintf(fp, "<p>");
		TSPrintValue (fp, temp->Data);
		if (GuideMode==1)
		{
			if (temp==MenuPtr->Current)
				printf("\t <-You are here");
			if (temp== MenuPtr->LastNode)
				printf("\t <-Last Node inserted");
		}
		if (bonus==1)
			fprintf(fp, "</p>");
		fprintf(fp, "\n");
		temp=temp->Next;
		while(temp!=NULL)
		{
			for (i=0; i<tabs; i++)
				fprintf(fp, "\t");
			if (bonus==1)
				fprintf(fp, "<p>");
			TSPrintValue (fp, temp->Data);
			if (GuideMode==1)
			{
				if (temp==MenuPtr->Current)
					printf("\t <-You are here");
				if (temp== MenuPtr->LastNode)
					printf("\t <-Last Node inserted");
			}
			if(bonus==1)
				fprintf(fp, "</p>");
			fprintf(fp, "\n");
			temp=temp->Next;
		}
	}
	else
	{
		for (i=0; i<tabs; i++)
			fprintf(fp, "\t");
		if(bonus==1)
			fprintf(fp, "<h%d>", tabs);
		TSPrintValue (fp, temp->Data);
		if (GuideMode==1)
			{
				if (temp==MenuPtr->Current)
					printf("\t <-You are here");
				if (temp== MenuPtr->LastNode)
					printf("\t <-Last Node inserted");
			}
		if(bonus==1)
			fprintf(fp, "</h%d>", tabs);
		fprintf(fp, "\n");
		if(temp->Down->Next!=NULL)
			RecEktuposi (MenuPtr, temp->Down->Next, tabs+1, GuideMode, bonus, fp); /*to ->Next gia na min ektuposi tin kefali*/
		if (temp->Next!=NULL)
			RecEktuposi (MenuPtr, temp->Next, tabs, GuideMode, bonus, fp);
	}
}
/**********************************************************************************************************************************/

int MenuEktuposiKatigorias (InfoMenuPtr MenuPtr)
{
	if(MenuPtr->Current->Prev!=NULL)  /*elegxos an einai se kefali*/
		return 0;
	if(MenuPtr->Current->Next==NULL)
		return -1;					/*elegxos an einai keni i katigoria*/
	if(MenuPtr->Current->Prev==NULL && MenuPtr->Current->Up==NULL)
	{
		printf("Menou tis epixeirisis: %s\n", MenuPtr->Name);
	}
 	RecEktuposi (MenuPtr, MenuPtr->Current->Next, 0, 0, 0, stdout); /*to ->Next gia na min ektuposi tin kefali*/
	return 1;
}
	
int MenuMetakinisiMeta (InfoMenuPtr MenuPtr)
{
	MenuNodePtr temp;
	if(MenuPtr->Current->Next==NULL) /*Teleutaioi komvoi*/
		return 0;
	else if(MenuPtr->Current->Prev==NULL)
		return -1;					/*kefales*/
	temp=MenuPtr->Current->Next;
	MenuPtr->Current->Next=temp->Next;
	if(temp->Next!=NULL)
		temp->Next->Prev==MenuPtr->Current;
	MenuPtr->Current->Prev->Next=temp;
	temp->Prev=MenuPtr->Current->Prev;
	MenuPtr->Current->Prev=temp;
	temp->Next=MenuPtr->Current;
	return 1;	
}

int MenuMetakinisiPrin (InfoMenuPtr MenuPtr)
{
	MenuNodePtr temp;
	if(MenuPtr->Current->Prev->Prev==NULL)				/*Protoi Komvoi*/
		return 0;	
	else if (MenuPtr->Current->Prev==NULL)				/*Kefales*/
		return -1;
	temp=MenuPtr->Current->Prev;
	temp->Prev->Next=MenuPtr->Current;
	MenuPtr->Current->Prev=temp->Prev;
	temp->Next=MenuPtr->Current->Next;
	temp->Prev=MenuPtr->Current;
	MenuPtr->Current->Next=temp;
	return 1;
}

int MenuDiagrafiKatigorias (InfoMenuPtr MenuPtr)
{
	MenuNodePtr temp, temp1;
	if (MenuPtr->Current->Next==NULL) //den uparxei komvos next
		return 0;
	if (MenuPtr->Current->Next->Down->Next!=NULL)
		if(MenuPtr->Current->Next->Down->Next->Data.Category==1) //exei upokatigories
			return -1;
	temp=MenuPtr->Current->Next->Down;
	temp1=temp->Next;
	do
	{
		free(temp);
		temp=temp1;
		if(temp1!=NULL)
		temp1=temp1->Next;
	}
	while (temp1!=NULL);
	if (temp!=NULL)
	free(temp);	
	temp=MenuPtr->Current->Next;	
	MenuPtr->Current->Next=temp->Next;
	if (temp->Next!=NULL)
		temp->Next->Prev=MenuPtr->Current;
	free(temp);
	return 1;
}

/*Boithitiki Sunartisi gia na ulopoiithei i anadromi*/
/*************************************************************************************************************/
void Rec_Diagrafi (InfoMenuPtr MenuPtr, MenuNodePtr NodePtr)
{
	MenuNodePtr temp, temp1=NULL;
	if (NodePtr->Next!=NULL)
	{
		if (NodePtr->Next->Data.Category==0)
		{
			temp=NodePtr->Next;
			if(temp->Next!=NULL)
			temp1=temp->Next;
			do
			{
				free(temp);
				temp=temp1;
				if(temp1!=NULL)
					temp1=temp1->Next;
			}
			while (temp1!=NULL);
			if (temp!=NULL)
			free(temp);
			NodePtr->Next=NULL;
		}
		else if(NodePtr->Next->Data.Category==1)
		{
			Rec_Diagrafi(MenuPtr, NodePtr->Next->Down);
			if(NodePtr->Next->Next!=NULL)
				Rec_Diagrafi(MenuPtr, NodePtr->Next->Next->Down);
			free(NodePtr->Next);
			if(NodePtr->Up!=MenuPtr->Current)
			{
				free(NodePtr);
				if(NodePtr->Up!=NULL)
					NodePtr->Up->Down=NULL;
			}
			else 
				NodePtr->Next=NULL;
		}
	}
	else
	{
			if(NodePtr->Up!=MenuPtr->Current)
			{
				free(NodePtr);
				if(NodePtr->Up!=NULL)
					NodePtr->Up->Down=NULL;
			}
			else 
				NodePtr->Next=NULL;
	}
}
/*****************************************************************************************************************/

int MenuDiagrafiOlon (InfoMenuPtr MenuPtr)
{
	MenuNodePtr temp;
	 if(MenuPtr->Current->Down==NULL)
	 	return 0;
	Rec_Diagrafi (MenuPtr, MenuPtr->Current->Down);
	return 1;
}

int MenuCut(InfoMenuPtr *pointer)
{
	if ((*pointer)->Current->Prev==NULL)
		return 0; //kefali
	(*pointer)->CutToPaste=(*pointer)->Current;
	(*pointer)->Current=(*pointer)->Current->Prev;
	(*pointer)->Current->Next=(*pointer)->CutToPaste->Next;
	if((*pointer)->Current->Next!=NULL)
	(*pointer)->Current->Next->Prev=(*pointer)->Current;
	return 1;
}

int MenuPaste (InfoMenuPtr (*pointer))
{
	MenuNodePtr temp;
	temp=(*pointer)->Current->Next;
	(*pointer)->Current->Next=(*pointer)->CutToPaste;
	(*pointer)->CutToPaste->Prev=(*pointer)->Current;
	(*pointer)->CutToPaste->Next=temp;
	if(temp!=NULL)
	temp->Prev=(*pointer)->CutToPaste;
	(*pointer)->CutToPaste->Up=(*pointer)->Current->Up;
	(*pointer)->Current=(*pointer)->CutToPaste;
	(*pointer)->CutToPaste=NULL;
	return 1;
}

int MenuDestruction(InfoMenuPtr *pointer)
{
	MenuNodePtr temp;
	if((*pointer)->Start->Next==NULL)
	{
		free((*pointer)->Start);
		free((*pointer));
		return 1;
	}
	(*pointer)->Current=(*pointer)->Start->Next;
	do
	{
		if ((*pointer)->Current!=NULL)
			temp=(*pointer)->Current->Next;
		MenuDiagrafiOlon((*pointer));
		free((*pointer)->Current->Down);
		free((*pointer)->Current);
		(*pointer)->Current=temp;
	} while((*pointer)->Current!=NULL);
	free((*pointer)->Start);
	free((*pointer));
	return 1;
}
		
int MenuEktuposiFull (InfoMenuPtr MenuPtr)
{
	if(!MenuKeniKatigoria(MenuPtr))
		return 0;
	printf("Menou tis epixeirisis: %s\n", MenuPtr->Name);
	RecEktuposi (MenuPtr, MenuPtr->Start->Next, 0, 1, 0, stdout);
	return 1;
}

int MenuBonusOutput (InfoMenuPtr MenuPtr, FILE *fp)
{
	if (!MenuKeniKatigoria(MenuPtr))
		return 0;
	fprintf(fp, "<html>\n\n<head>\n");
	fprintf(fp, "<title>Menou tis epixeirisis: %s</title>\n", MenuPtr->Name);
	fprintf(fp, "</head>\n\n<body>\n");
	RecEktuposi (MenuPtr, MenuPtr->Start->Next, 1, 0, 1, fp);
	fprintf(fp, "</body>\n</html>");
	return 1;
}
