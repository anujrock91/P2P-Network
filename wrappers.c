#include "network.h"


int Socket(int family, int type, int protocol){
	int val;
	if((val=socket(family,type,protocol))<0){
		perror(val);
	}
	return(n);
}
