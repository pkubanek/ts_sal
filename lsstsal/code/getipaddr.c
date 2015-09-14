#include <sys/unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

int main()
{
 char hostname[128];
 int i;
 struct hostent *he;
 struct in_addr **addr_list;
 struct in_addr addr;

 gethostname(hostname, sizeof hostname);
 printf("My hostname: %s\n", hostname);

 he = gethostbyname(hostname);

 if (he == NULL) { // do some error checking
   herror("gethostbyname"); // herror(), NOT perror()
   return 1;
 }

 // print information about this host:
 printf("Official name is: %s\n", he->h_name);
 printf("IP address: %s\n", inet_ntoa(*(struct in_addr*)he->h_addr));
 printf("All addresses: ");
 addr_list = (struct in_addr **)he->h_addr_list;

 for(i = 0; addr_list[i] != NULL; i++) {
   printf("%s ", inet_ntoa(*addr_list[i]));
 }

 printf("\n");

 return 0;
}

