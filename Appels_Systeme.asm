global Appel_Systeme_Video
global Appel_Systeme_Clavier

extern CallBack_INT_Video
extern CallBack_INT_Clavier

Appel_Systeme_Video:
  push ecx   ; Passage en paramètres des valeurs de registre
  push ebx 
  push eax  ; on empille à l'envers par rapport aux paramètres du C
  call CallBack_INT_Video
  pop eax
  pop ebx
  pop ecx
  iret


Appel_Systeme_Clavier:

  push ebx  ; sauvegarde de ebx
  push eax  ; on empile le paramètre
  call CallBack_INT_Clavier  ; le code scan sera stocké dans al
  pop ebx  ; on dépile le paramètre
  pop ebx  ; restitution de ebx
  iret  ; dans al il y a le code scan

