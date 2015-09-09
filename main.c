/*Kωνσταντίνος Στεφανίδης-Βοζίκης Α.Μ.:1115201400192*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Menu.h"

void print_options (InfoMenuPtr Menu, InfoMenuPtr CafeMenu)
{
	if(Menu==NULL)
	{
		printf("Den uparxei menou gia kapoio magazi akoma\n");
	}
	else
	{
		printf("\nTo epilegmeno magazi einai: ");
		if(Menu==CafeMenu)
			printf("i kafeteria\n");
		else
			printf("to estiatorio\n");
	}
	printf("\n"); 			/*aisthitikoi logoi*/
	printf("1.  Αλλαγή Μαγαζιού\n");
	printf("2.  Dimiourgia Menou\n");
	printf("3.  Elegxos kenis katigorias\n");
	printf("4.  Eisagogi komvou\n");
	printf("5.  Ektuposi periexomenon komvou\n");
	printf("6.  Allagi periexomenon komvou\n");
	printf("7.  Epomenos Komvos\n");
	printf("8.  Proigoumenos Komvos\n");
	printf("9.  Metakinisi komvou meta\n");
	printf("10. Metakinisi komvou prin\n");
	printf("11. Metakinisi sto pano epipedo\n");
	printf("12. Metakinisi sto kato epipedo\n");
	printf("13. Ektuposi katigorias\n");
	printf("14. Diagrafi katigorias\n");
	printf("15. Diagrafi katigorias kai upokatigorion\n");
	printf("16. Apokopi komvou\n");
	printf("17. Epikollisi komvou\n");
	printf("18. Katastorfi Menou\n");
	printf("19. Ektuposi onomatos magaziou\n");
	printf("20. Ektuposi olou tou menou\n");
	printf("21. Bonus\n");
	printf("22. Exit\n");
	printf("\n");			/*aisthitikoi logoi*/
}

int main(int argc, char *argv[]) {

	int 			option, magazi, end=0, res, mark;	
	InfoMenuPtr 	FoodMenu=NULL, CafeMenu=NULL, Menu=NULL;
	FILE *fp;
	printf("Gia ektuposi ton diathesimon epilogon patiste 0\n");
	Menu=FoodMenu;
	while (end!=1)
	{
		printf("Doste epilogi 1-19\n");
		scanf("%d", &option);
		getchar();
		while (option<0 || option>22)
		{
			printf("Sorry bro invalid option, please retry\n");
			scanf("%d", &option);
		}
		printf("\n");			/*aisthitikoi logoi*/
		switch (option)
		{
			case 0:
				print_options(Menu, CafeMenu);
				break;
			case 1:
				if (FoodMenu==NULL || CafeMenu==NULL)
				{
					
					printf("Parakalo dimiourgiste kai ta 2 menou prota\n");
					break;
				}
				printf("Epilexthike ");
				if(Menu==FoodMenu)
				{
					Menu=CafeMenu;
					printf("i kafeteria\n");
				}
				else
				{
					Menu=FoodMenu;
					printf("to estiatorio\n");
				}
				break;
			case 2:
				printf("Thelete na dimiourgisete menu gia estiatorio i kafeteria (1/2)?\n");
				scanf("%d", &magazi);
				Menu=NULL;
				if(!MenuDimiourgia(&Menu))
				{
					fprintf(stderr, "I dimiourgia apetyxe, to programma termatizetai\n");
					return -1;
				}		
				else
					printf("To menou dimiourgithike epituxos!\n");
				if (magazi==1)
					FoodMenu=Menu;
				else
					CafeMenu=Menu;
				break;
			case 3:
				if(!MenuKeniKatigoria(Menu))
					printf("To menou einai keno!\n");
				else printf("To menou dn einai keno!\n");
				break;
			case 4:
				if(!MenuEisagogiKomvou(Menu))
				{
					fprintf(stderr, "Den mporese na ginei eisagogi komvou, to programma termatizetai\n");
					return -1;
				}
				else printf("O komvos eisixthi epituxos\n");
				break;
			case 5:
				if(!MenuEktuposiKomvou(Menu))
					fprintf(stderr, "Den ginetai na ektupothei kefali listas\n");
				break;
			case 6:
				if(!MenuAllagiPeriexomenou(Menu))
					fprintf(stderr, "Den mporese na allaxthei to periexomeno tou komvou (sfalma mnimis)\n");
				break;
			case 7:
				if(!MenuEpomenos(&Menu))
					fprintf(stderr, "Den uparxei epomenos komvos\n");
				break;
			case 8:
				if(!MenuProigoumenos(&Menu))
					fprintf(stderr, "Vriskesai se kefali\n");
				break;
			case 9:
				res=MenuMetakinisiMeta(Menu);
				if(res==0)
					fprintf(stderr, "Eisai ston teleutaio komvo, den na ton pas pio mprosta\n");
				else if (res==-1)
					fprintf(stderr, "Den mporeis na metakiniseis mia kefali\n");
				else
					printf("O komvos metakinithike mia thesi mprosta\n");
				break;
			case 10:
				res=MenuMetakinisiPrin(Menu);
				if (res==0)
					fprintf(stderr, "Eisai ston proto komvo, den ginetai na ton pas pio piso\n");
				else if(res==-1)
					fprintf(stderr, "Den mporeis na metakiniseis mia kefali\n");
				else
					printf("O komvos metakinithike mia thesi piso\n");
				break;
			case 11:
				if(!MenuPano(&Menu))
				fprintf(stderr, "Vriskesai sto proto epipedo den ginetai na pas pio pano\n");
				break;
			case 12:
				if(!MenuKato(&Menu))
					fprintf(stderr, "Vriksesai sto teleutaio epipedo, den ginetai na pas pio kato\n");
				break;
			case 13:
				res=MenuEktuposiKatigorias(Menu);
				if (res==0)
					fprintf(stderr, "Den eisai se komvo kefali\n");
				else if(res==-1)
					fprintf(stderr, "I katigoria pou thes na ektuposeis einai keni\n");
				break;
			case 14:
				if(!MenuDiagrafiKatigorias(Menu))
					fprintf(stderr, "Auto pou pas na diagrapseis exei upokatigoria\n");
				else
					printf("I katigoria diegrafi epituxos\n");
				break;
			case 15:
				if(!MenuDiagrafiOlon(Menu))
					fprintf(stderr, "Auto pou prospatheis na diagrapseis dn exei periexomena");
				break;
			case 16:
				if(!MenuCut(&Menu))
					fprintf(stderr, "Den ginetai na metakiniseis kefali\n");
				break;
			case 17:
				if(!MenuPaste(&Menu))
					fprintf(stderr, "Den uparxei epilegmenos komvos gia na metakiniseis\n");
				break;
			case 18:
				if(Menu==NULL)
				{
					fprintf(stderr, "Den mporeis na katastrepseis anuparkto menu\n");
					break;
				}
				if(Menu==FoodMenu)
				 mark=1;
				else
				 mark=2;
				if(MenuDestruction(&Menu))
					printf("To menou katastrafike\n");
				if(mark==1 && CafeMenu!=NULL)
				{
					Menu=CafeMenu;
					printf("Epilexthike to menou tis kafeterias\n");
				}
				else if(mark==2 && FoodMenu!=NULL)
				{
					Menu=FoodMenu;
					printf("Epilexthike to menou tou estiatoriou\n");
				}
				else
					printf("Den uparxei diathesimo menou pleon, dimiourgiste kapoio gia na sunexisete i patiste 22 gia eksodo\n");
					Menu=NULL;
				break;					
			case 19:
				if(Menu==NULL)
				{
					fprintf(stderr, "Den uparxei magazi gia na ektupothei to onoma tou\n");
					break;
				}
				PrintBusinessName(Menu);
				break;
			case 20:
				if (Menu==NULL)
					break;
				if(!MenuEktuposiFull(Menu))
					fprintf(stderr, "Den uparxei menou gia na ektupothei\n");
				break;
			case 21:
				fp=fopen("./Menu.html", "w");
				if(!MenuBonusOutput(Menu, fp))
					fprintf(stderr, "Den uparxei menou gia na ektupothei\n");
				else
					printf("To menou ektupothike epituxos to arxeio Menu.html\n");
				fclose(fp);
				break;
			case 22:
				end=1;
				break;
		}
		printf("\n");	/*aisthitikoi logoi*/
	}
	getchar();	
	return 0;
}
