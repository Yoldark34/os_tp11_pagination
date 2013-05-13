/* 
 * File:   API.h
 * Author: Administrateur
 *
 * Created on 28 avril 2013, 22:34
 */

#ifndef API_H
#define	API_H
#include "type.h"

void API_clrscr();
void API_puts(char* P_Message, BYTE color);
int API_Attendre_Scan_Code(); 

#endif	/* API_H */

