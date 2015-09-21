/*
	generic_Daemon.c
	
	Support functions for publisher/subscriber handling
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <mqueue.h>
#include <assert.h>
#include <semaphore.h>


static int n_fds, n_fd_sub, fd_sub[64], n_fd_pub, fd_pub[64];
static char name_sub[8192], name_pub[8192];

void initFlags()
{       
	n_fds = 0;
        n_fd_sub = 0;
        n_fd_pub = 0;
}




int newPub(char *pname, int *np, int *nfd)
{
/*
			Handle new publisher logic
*/
	char name[128];
	
	strcpy(name, pname);
        if (n_fd_pub == 0)
        {
         	n_fd_pub = 1;
                n_fds++;
                fd_pub[0] = n_fds;
                strcpy(name_pub, name);
        }
        else
        {
                n_fds++;
                fd_pub[n_fd_pub] = n_fds;
                strcat(name_pub, " ");
                strcat(name_pub, name);
                n_fd_pub++;
        }
	*np = n_fd_pub;
	*nfd = n_fds;
	return(1);
}

int newSub(char *pname, int *ns, int *nfd)
{
/*
			Handle new subscriber logic
*/
	char name[128];
	
	strcpy(name, pname);
	if (n_fd_sub == 0)
        {
        	n_fd_sub = 1;
                n_fds++;
                fd_sub[0] = n_fds;
                strcpy(name_sub, name);
        }
        else
       	{
                 n_fds++;
                 fd_sub[n_fd_sub] = n_fds;
                 strcat(name_sub, " ");
                 strcat(name_sub, name);
                 n_fd_sub++;
         }
	 *ns = n_fd_sub;
	 *nfd = n_fds;
	 return(1);
}

int getPubFd(int k)
{
	int j, i;
	
	j = -1;
        for (i = 0; i < n_fd_pub; i++)
        {
        	if (k == fd_pub[i])
                {
                	j = i;
                        break;
               	}
        }
	return(j);
}
	


 
