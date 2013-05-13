#include "Ecran.h"
#include "Outils.h"

/*
 EAX :
 * 0 : effacer l'écran
 *     BH : caractère, BL : attribut
 * 1 : positionner le curseur
 *    BH : X, BL : Y
 * 2 : Affiche un Caractère
 *       BH : caractère, BL : attribut
 * 3 : Affiche Une Chaine
 *      EBX : adresse de la chaine
 */


//##############################################################################
void CallBack_INT_Video(UINT32 P_EAX, UINT32 P_EBX, UINT32 P_ECX) // lecture dans la pile
{
    Affiche_Chaine("-- CallBack_INT_Video --> EAX: ");
    Affiche_Chaine(Entier_Vers_Chaine(P_EAX));
    Affiche_Chaine("    EBX: ");
    Affiche_Chaine(Entier_Vers_Chaine(P_EBX));
     Affiche_Chaine("    ECX: ");
    Affiche_Chaine(Entier_Vers_Chaine(P_ECX));
    
    Affiche_Caractere('\n');
    
    switch (P_EAX) {
        case 0 : Remplir_Ecran( (P_EBX>>8)&0xFF, P_EBX&0xFF); break;
        case 1 : Positionne_Curseur((P_EBX>>8)&0xFF, P_EBX&0xFF); break;
        case 2 : Regle_Couleur(P_EBX&0xFF);
                 Affiche_Caractere((P_EBX>>8)&0xFF); break;
        case 3 : Affiche_Chaine((UCHAR*)P_EBX); break;         
        
    }
    
    
}
