/***************************************************************************
                          conf_parser.c  -  Parsing del fichero de
                          			configuracion
                             -------------------
    begin                : dom feb 9 2003
    copyright            : (C) 2003 by Grupo WorldSpace
    email                : neuralgya@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "w3d_base.h"
#include "globales.h"

#include "conf_parser.h"

#define SEPARADORES "#=:, \t\n"

int establece_var_conf_numero(FILE * fl_fichero, char *s_token)
{

    char s_linea[LON_BUFF];
    char token[LON_BUFF];
    char valor[LON_BUFF];
    char s_aux[LON_BUFF];
    int  i_ini_token = 0;
    int  i_fin_token = 0;
    int  i_ini_valor = 0;
    int  i_fin_valor = 0;
    int  j, k = NO;
	uint i;

    T_FUNC_IN;
	
	while (!feof(fl_fichero))
	{
        if (fgets(s_linea, LON_BUFF, fl_fichero) != NULL) {

            if (s_linea[0] == '\n')
                continue;

            i_ini_token = strspn(s_linea, SEPARADORES);
            i_fin_token = strcspn(&s_linea[i_ini_token], SEPARADORES);
            i_fin_token += i_ini_token;

            strcpy(token, &s_linea[i_ini_token]);
            token[i_fin_token - i_ini_token] = '\0';

            strcpy(s_aux, &s_linea[i_fin_token + 1]);

            i_ini_valor = strspn(s_aux, SEPARADORES);

            i_fin_valor = strcspn(&s_aux[i_ini_valor], SEPARADORES);
            i_fin_valor += i_ini_valor;

            strcpy(valor, &s_aux[i_ini_valor]);
            valor[i_fin_valor - i_ini_valor] = '\0';

            j = 0;
            for (i = 0; i <= strlen(token); i++) {
                if (token[i] != ' ') {
                    s_linea[j] = toupper(token[i]);
                    j++;
                }
            }
            strcpy(token, s_linea);

            j = 0;
            for (i = 0; i <= strlen(valor); i++) {
                if (valor[i] != ' ') {
                    s_linea[j] = valor[i];
                    j++;
                }
            }
            strcpy(valor, s_linea);

            for (i = 0; i <= strlen(s_token); i++) {
                s_linea[i] = toupper(s_token[i]);
            }

            if (strcmp(s_linea, token) == 0) {
                log_msj("[conf_parser.c] Token:\"%s\" Valor:\"%d\" .\n",
                        token, atoi(valor));
                k = atoi(valor);
            }

        }

    }

    rewind(fl_fichero);

    T_FUNC_OUT return k;
}

char *establece_var_conf_cadena(FILE * fl_fichero, char *s_token)
{

    char s_linea[LON_BUFF];
    char token[LON_BUFF];
    char valor[LON_BUFF];
    char s_aux[LON_BUFF];
    int  i_ini_token = 0;
    int  i_fin_token = 0;
    int  i_ini_valor = 0;
    int  i_fin_valor = 0;
    int  j;
    char *k = NULL;
	uint i;

    T_FUNC_IN;

	while (!feof(fl_fichero))
	{
        if (fgets(s_linea, LON_BUFF, fl_fichero) != NULL)
		{
            if (s_linea[0] == '\n')
                continue;

            i_ini_token = strspn(s_linea, SEPARADORES);
            i_fin_token = strcspn(&s_linea[i_ini_token], SEPARADORES);
            i_fin_token += i_ini_token;

            strcpy(token, &s_linea[i_ini_token]);
            token[i_fin_token - i_ini_token] = '\0';

            strcpy(s_aux, &s_linea[i_fin_token + 1]);

            i_ini_valor = strspn(s_aux, SEPARADORES);

            i_fin_valor = strcspn(&s_aux[i_ini_valor], SEPARADORES);
            i_fin_valor += i_ini_valor;

            strcpy(valor, &s_aux[i_ini_valor]);
            valor[i_fin_valor - i_ini_valor] = '\0';

            for (i=0, j=0 ; i <= strlen(token); i++)
			{
                if (token[i] != ' ')
				{
                    s_linea[j] = toupper(token[i]);
                    j++;
                }
            }
            strcpy(token, s_linea);

            j = 0;
            for (i = 0; i <= strlen(valor); i++) {
                if (valor[i] != ' ') {
                    s_linea[j] = valor[i];
                    j++;
                }
            }
            strcpy(valor, s_linea);

            for (i = 0; i <= strlen(s_token); i++) {
                s_linea[i] = toupper(s_token[i]);
            }

            if (strcmp(s_linea, token) == 0) {
                log_msj("[conf_parser.c] Token:\"%s\" Valor:\"%s\" .\n",
                        token, valor);
                k = (char *) malloc(LON_BUFF);
                strcpy(k, valor);
            }

        }

    }

    rewind(fl_fichero);

    T_FUNC_OUT return k;
}
