/*Kωνσταντίνος Στεφανίδης-Βοζίκης Α.Μ.:1115201400192*/
#ifndef __MENU__
#define __MENU__

#include "TyposStoixeiouMenu.h"

typedef struct InfoMenu *InfoMenuPtr; // Ο Τύπος δείκτη σε Πληροφοριακό Κόμβο Μενού

int MenuDimiourgia 			(InfoMenuPtr *pointer);
void PrintBusinessName 		(InfoMenuPtr MenuPtr);
int MenuKeniKatigoria 		(InfoMenuPtr MenuPtr);
int MenuEisagogiKomvou 		(InfoMenuPtr MenuPtr);
int MenuEktuposiKombou 		(InfoMenuPtr MenuPtr);
int MenuAllagiPeriexomenou 	(InfoMenuPtr MenuPtr);
int MenuEpomenos 			(InfoMenuPtr *pointer);
int MenuProigoumenos 		(InfoMenuPtr *pointer);
int MenuPano 				(InfoMenuPtr *pointer);
int MenuKato 				(InfoMenuPtr *pointer);
int MenuEktuposiKatigorias 	(InfoMenuPtr MenuPtr);
int MenuDiagrafiKatigorias 	(InfoMenuPtr MenuPtr);
int MenuDiagrafiOlon 		(InfoMenuPtr MenuPtr);
int MenuMetakinisiMeta 		(InfoMenuPtr MenuPtr);
int MenuMetakinisiPrin 		(InfoMenuPtr MenuPtr);
int MenuCut 				(InfoMenuPtr *pointer);
int MenuPaste				(InfoMenuPtr *pointer);
int MenuDestruction			(InfoMenuPtr *pointer);
int MenuEktuposiFull 		(InfoMenuPtr MenuPtr);
int MenuBonusOutput 		(InfoMenuPtr MenuPtr, FILE *fp);	

#endif
