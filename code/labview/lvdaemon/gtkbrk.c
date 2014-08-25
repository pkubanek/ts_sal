/********************************************************************

        Get next token from string and returns break character.
        Returns also updated input pointer.
*/

char *gtkbrk(string, token, bchar)
char *string, *token, *bchar;
{
        char c;
        int i;

        i = 0;
        while ( (c = *string++) != 0)
        {
            if ((c == ' ') || (c == '\t'))      /* skip white space         */
            {
                if (i == 0) continue;       /* no token yet             */
                else        break;          /* true break               */
            }
            if (c < ' ') break;
            if (c == ',') break;            /* break characters         */
            if (c == ';') break;
            *token++ = c;
            i++;
        }
        *token++ = '\0';                    /* null terminate the string */
        *bchar = c;                         /* break character           */
        if (c == '\0') --string;
        return (string);                    /* return updated pointer    */
}

