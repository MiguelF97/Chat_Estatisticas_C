#include <stdio.h>
#include <stdlib.h>
#include "conversa.h"

int main()
{
    Conversa * c;
    c = newconversa();
    char str[80] = "ola ola xd ola ola xd ola ola xd ola ola xd ola ola xd";
    Mensagem * m = newmensagem2(str);
    novaMensagem(c,m);


    Palavra * p = getPalavra(getMensagem(c,0),2);
    printf("%s",p->text);
    return 0;
}

