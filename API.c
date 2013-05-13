#include "type.h"

//############################################################################## 
// VIDEO 
//############################################################################## 
void API_clrscr() 
{ 
   asm (".intel_syntax noprefix "); 
   asm ("mov eax,0");        /// 0 :code effacer l'écran 
   asm ("mov ebx,0x2007");       // caractère espace en blanc sur fond noir 
   asm ("int 0xA0"); 
   asm (".att_syntax noprefix \n"); 
} 
//------------------------------------------------------------------------------ 

//void API_puts(char* P_Message, BYTE P_Couleur) 
//{ 
//     
//    asm("mov %0, %%ebx;" 
//       "mov $0x03, %%eax;"
//       "mov %1, %%ecx;"
//       "int $0xA0" :: "m" (P_Message), "m" (P_Couleur)); 
// 
//} 

void API_puts(char* P_Message, BYTE color)
{ 
     
    asm("mov %0, %%ebx;"
			"mov $0x05, %%eax;"
			"mov %1, %%ecx;"
			"int $0xA0" ::"m" (P_Message), "m" (color));
}

void API_fill(char* P_Message, int qty) {

	asm("mov %0, %%ebx;"
			"mov $0x05, %%eax;"
			"mov %1, %%ecx;"
			"int $0xA0" ::"m" (P_Message), "m" (qty));
}



//############################################################################## 
// CLAVIER 
//############################################################################## 
int API_Attendre_Scan_Code() 
{ 
   asm (".intel_syntax noprefix "); 
   asm ("mov eax,1");      // 1 : code lecture scan code 
   asm ("int 0xA1");      // dans AX il y aura le scan code 
   asm (".att_syntax noprefix \n"); 
} 
