#include "stdafx.h"
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>


bool get_host_ip(const char* szHost,std::vector<std::string> &v);
{
	struct hostent     *myent;
	struct in_addr  myen;
	long int *add;

	myent = gethostbyname(szHost);
	if (myent == NULL)
	{
		return false;
	}

	printf("%s\n", myent->h_name);

	while(*myent->h_addr_list != NULL)
	{
		add = (long int *)*myent->h_addr_list;
		myen.s_addr = *add;
		v.push_back(inet_ntoa(myen));
		printf("%s\n", inet_ntoa(myen));
		myent->h_addr_list++;
	}
	return true;
}


#define TRUE 1

void prthost(struct hostent *h);

main(int argc, char *argv[])
{
	struct hostent *h;

	/* sethostent() opens the prefix.ETC.HOSTS file, or when using a  */
	/* nameserver, opens a TCP connection to the nameserver.          */

	sethostent(TRUE);

	/* gethostent() reads the next sequential entry in the            */
	/* prefix.ETC.HOSTS file. It returns a pointer to a "hostent"     */
	/* structure.                                                     */

	while (h=gethostent())
		prthost(h);

	/* endhostent() closes the prefix.ETC.HOSTS file, or the          */
	/* connection to the nameserver.                                  */

	endhostent();
	exit(EXIT_SUCCESS);
}


static void prthost(struct hostent *h)
{
	char **p;

	/* Print primary name and aliases. */
	printf("\nname: %s\n",h->h_name);
	for (p=h->h_aliases; *p; p++)
		printf("alternate name: %s\n",*p);

	/* Handle unexpected situations gracefully. */
	if (h->h_addrtype != AF_INET) {
		printf("Not an internet address.\n");
		return;
	}
	if (h->h_length != sizeof(struct in_addr)) {
		printf("Invalid length: %d.\n",h->h_length);
		return;
	}

	/* Print the primary address and any alternates.  */
	for (p=h->h_addr_list; *p; p++) {
		printf("%s address: %s\n",
			p==h->h_addr_list ? "primary " : "alternate ",
			inet_ntoa((*(struct in_addr *)*p)) );
	}
}
