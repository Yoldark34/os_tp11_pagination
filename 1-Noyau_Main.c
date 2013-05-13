#include "type.h"
#include "Ecran.h"
#include "Outils.h"
#include "Info_Boot.h"
#include "Init_GDT.h"
#include "Init_IDT.h"
#include "MACRO.h"
#include "PLAN_MEMOIRE.h"
#include "HARD_8042_Clavier.h"

#include "API.h"
#include "convert_keyboard.h"
#include "Pagination.h"
#include "Allocation_Pages.h"




void OS_Main();

//----------------------------------------------------------------------------
void Affiche_Informations_Boot(T_BOOT_INFO* P_Info)
{
 if ( (P_Info->Flags & BOOT_INFO_MEMOIRE) == BOOT_INFO_MEMOIRE) {
    Regle_Couleur(BLANC); Affiche_Chaine(">>>Memoire detectee : " );
    UINT32 L_Taille_Memoire =P_Info->Adresse_Basse +P_Info->Adresse_Haute + 1024;
    Regle_Couleur(BLEU| LUMINEUX); Affiche_Chaine(Entier_Vers_Chaine(L_Taille_Memoire/1024) );
    Affiche_Chaine(" Mo \n" );
  }
}
//----------------------------------------------------------------------------
void Affiche_Message(UCHAR* P_Message, UCHAR* P_Etat)
{
  Regle_Couleur(BLANC); Affiche_Chaine(P_Message);
  Positionne_Curseur(78-Taille_Chaine(P_Etat),Donne_Curseur_Y());
  Regle_Couleur(VERT | LUMINEUX); Affiche_Chaine(P_Etat);
  Affiche_Caractere('\n');
}
 //----------------------------------------------------------------------------



 //----------------------------------------------------------------------------
void OS_Start(T_BOOT_INFO* P_Info)
{
  Efface_Ecran();
  Affiche_Message(">>>BOOT JLV OS V1 - 2011 Via GRUB : ", "OK");
  Affiche_Informations_Boot(P_Info);

  Initialisation_GDT();
  Affiche_Message(">>>Initialisation de la GDT : ","OK");

  //Initialiser le pointeur pile.
  // NE PAS ETRE DANS UNE FONCTION CAR à la sortie d'une fonction, le regsitre ESP est réinitialisé à la valeur précédant l'appel.
 //  INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU,DEBUT_STACK_NOYAU);


  INITIALISE_SS_ESP(SELECTEUR_STACK_NOYAU, DEBUT_STACK_NOYAU)
   OS_Main();
   asm ("NOP");
}
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
void OS_Main() {
	Affiche_Message(">>>Initialisation de la Pile (ESP) : ", "OK");

	Initialisation_IDT();
	Affiche_Message(">>>Initialisation de la IDT : ", "OK");

	Initialisation_Pagination();
	Affiche_Message(">>>Initialisation de la pagination : ", "OK");

	Inititialisation_8259A();
	Affiche_Message(">>>Initialisation du PIC 8259A : ", "OK");

	Initialisation_8253(1193);
	Affiche_Message(">>>Initialisation du controleur 8253 : ", "OK");

	AUTORISE_INTERRUPTION;

	//Allocation de 4 pages à partir de l'adresse virtuelle 1 Go
	Allouer_Pages(ADRESSE_BASE_REPERTOIRE_TABLES_DE_PAGES_OS, 0x40000000, 4);

	Affiche_Chaine("Ecriture dans 0x40000000");
	UINT32* Data = (UINT32*) 0x40000000;
	*Data = 0x5555; //OK !!!

	Affiche_Chaine("\nAppyez sur une touche pour ecrire a une adresse 2Go\n");
	Attendre_Touche_Relache();

	Affiche_Chaine("Ecriture dans 0x80000000");

	UINT32* Danger = (UINT32*) 0x80000000;
	*Danger = 0x5555; //cela va générer une exception !!!

	Affiche_Chaine("FIN !!!!");

	while (1);
 }





