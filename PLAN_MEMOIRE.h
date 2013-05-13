#ifndef PLAN_MEMOIRE_H
#define	PLAN_MEMOIRE_H

#include "Descripteurs.h"

//##############################################################################
// PLAN MEMOIRE de l'OS (à mapper)
//    GDT en                              0x00000000           taille : 2Ko
//    IDT en                              0x00000800  (+2Ko)   taille : 2Ko
//------------------------------------------------------------------------------
//    le code est chargé par le grub à    0x00100000  (+1 Mo)  taille  ???
//    les data sont stockées en           0x00200000  (+2Mo)   taille  ???
//    Haut de la pile du noyau en         0x00300000  (+3Mo)   taille  ???
//------------------------------------------------------------------------------
//    Repertoire des tables de pages OS   0x00400000  (+4Mo)   taille : 4Ko
//    Tables de pages OS                  0x00401000  ( +4 Mo + 4 Ko)  taille : 4Mo
//    BitMap page Memoire                 0x00801000  (+8 Mo + 4Ko) taille: 128Ko
//------------------------------------------------------------------------------
//   Structures des tables Process        0x00821000  (+8Mo + 132Ko) occupe 256Mo => 64 process  
//##############################################################################
//  Process  débute en                    0x40000000
//------------------------------------------------------------------------------

#define TAILLE_OS                        0x10822000   // < 1 Go
#define TAILLE_PROCESS                    0xC0000000   // 3 Go

//============================================================================
//                             SEGMENTATION
//==============================================================================

//##############################################################################
//      Descripteurs de segments de 0x0000 à 0x7F8  ( 256 descripteur de 8 Octets)
//##############################################################################
#define ADRESSE_BASE_DESCRIPTEUR_SEGMENT    0x00000000  //A partir de 0
#define LIMITE_DESCRIPTEURS_SEGMENT         0xFF         // jusqu'à 2040  (2Ko - 8)


//##############################################################################
//      Descripteurs de guichet de 0x800 à 0xFF8 (256 descripteurs de 8 Octets)
//##############################################################################
#define ADRESSE_BASE_DESCRIPTEUR_GUICHET    0x00000800   // A partir de 2048 
#define LIMITE_DESCRIPTEURS_GUICHET         0xFF         // jusqu'à 4088 (4ko - 8)


//-----------------------------------------------------------------------------------
#define INDEX_DESCRIPTEUR_CODE_NOYAU     1
#define SELECTEUR_CODE_NOYAU            (INDEX_DESCRIPTEUR_CODE_NOYAU <<3)
#define BASE_CODE_NOYAU                 0x00000000
#define LIMITE_CODE_NOYAU               0xFFFFF     // de 0 à 0xFFFFF = 0x100000  0x100000* 4 Ko => 4Go


//-----------------------------------------------------------------------------------
#define INDEX_DESCRIPTEUR_DATA_NOYAU   2
#define SELECTEUR_DATA_NOYAU           (INDEX_DESCRIPTEUR_DATA_NOYAU<<3)
#define BASE_DATA_NOYAU         0x00000000
#define LIMITE_DATA_NOYAU       0xFFFFF     // de 0 à 0xFFFFF = 0x100000  0x100000* 4 Ko => 4Go

//-----------------------------------------------------------------------------------
#define INDEX_DESCRIPTEUR_STACK_NOYAU 3
#define SELECTEUR_STACK_NOYAU       (INDEX_DESCRIPTEUR_STACK_NOYAU <<3)
#define BASE_STACK_NOYAU           0x00         // 0 car dans un segment de pile, cete valeur n'est pas exploitée (le bit D sera à 0 donc 
                                  // début du haut de la pile à 4Go maxi. Sera réglée par ESP
#define LIMITE_STACK_NOYAU      0x000000      // autoriser de descendre jusqu'à 0 Mo -- MODIFIER CELA EN FIN                                              
#define DEBUT_STACK_NOYAU       0x00300000     // A partir de 3 Mo (réglé par ESP)
//-----------------------------------------------------------------------------------



//==============================================================================
//                             PAGINATION
//==============================================================================
#define TAILLE_TABLE_DE_PAGES           4096  // 1024 entrées de 32 bits
#define TAILLE_PAGE_MEMOIRE             4096   // le bit PS des entrées des tables sera à 0 !
#define NOMBRE_TOTAL_PAGES              0x100000 // 1024*1024 pages de 4ko => 4Go
#define NOMBRE_TOTAL_TABLES             1024
//------------------------------------------------------------------------------

#define NOMBRE_TABLES_PAGES_OS          (TAILLE_OS>>22)
#define NOMBRE_PAGES_OS                 (TAILLE_OS>>12)

#define NOMBRE_TABLES_PAGES_PROCESS     (TAILLE_PROCESS>>22) 
#define NOMBRE_PAGES_PROCESS            (TAILLE_PROCESS>>12)      
#define TAILLE_STRUCTURE_PAGES_UN_PROCESS ( (NOMBRE_TABLES_PAGES_PROCESS+1)*TAILLE_TABLE_DE_PAGES )


#define NOMBRE_PROCESS_MAXI              4 // 64                    // pour chaque process 1 table de repertoire et NOMBRE_TABLES_PAGES_PROCESS de tables


//==

//##############################################################################
//      Repertoire des Tables de Pages de 0x00400000 à  0x00401000 (1024 entrées de 32 bits)
//##############################################################################
#define ADRESSE_BASE_REPERTOIRE_TABLES_DE_PAGES_OS  0x00400000  // A partir de 4MO
                                                             // taille : 4Ko 

//##############################################################################
//     Tables de Pages de 0x401000 à  potentielement 0x801000 (1024 Tables soit 4Mo)
// Une table contient 1024 entrées de 32 bits
//##############################################################################
#define ADRESSE_BASE_TABLES_DE_PAGES  (ADRESSE_BASE_REPERTOIRE_TABLES_DE_PAGES_OS+ TAILLE_TABLE_DE_PAGES) //0x00401000  // A partir 4Mo + 4Ko
                                                  // Taille 1024*4Ko  => 4Mo
//------------------------------------------------------------------------------
#define ADRESSE_BASE_BITMAP_MEMOIRE    0x00801000
#define INDEX_BITMAP_MAXI              NOMBRE_TOTAL_PAGES>>3  // 1 bit par page
//------------------------------------------------------------------------------
//#define ADRESSE_BASE_TAS_PAGES_SYSTEME      0x00821000
//#define LIMITE_TAS_PAGES_SYSTEME            0x08821000

#define ADRESSE_BASE_STRUCTURE_PAGES_PROCESS    0x00821000
#define LIMITE_STRUCTURE_PAGES_PROCESS          0x08821000

#define ADRESSE_BASE_CONTEXTE_PROCESS          0x40000000

#endif	/* PLAN_MEMOIRE_H */

