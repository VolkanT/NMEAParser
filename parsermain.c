#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char nmeaHeaderSize = 6;
const char nmeaMessageSize = 82;

int main(void)
{
	// create file
	FILE * pOutput;
	pOutput = fopen("output","w");
	fclose(pOutput);

	printf("stream content, type \'q\' to exit ");
	
	//From input stream parse for GPRMC messages.
	char input[nmeaMessageSize];
	char * pfind; 
	char UTC[8];
	float lat = 0;
	float lon = 0;


	while(1)
	{
		fgets(input,nmeaMessageSize+1, stdin);

		// valid GPRMC Message?
		if((input[0] == '$') && (input[1] == 'G') && ((input[2] == 'P')) && 
		((input[3] == 'R')) && (input[4] == 'M') && (input[5] == 'C'))
		{
			// Extract UTC
			pfind = strchr(input,',');
			UTC[0] = pfind[1];
			UTC[1] = pfind[2];
			UTC[2] = ':';
			UTC[3] = pfind[3];
			UTC[4] = pfind[4];
			UTC[5] = ':';
			UTC[6] = pfind[5];
			UTC[7] = pfind[6];

			// Extract and convert latitude
			pfind = strchr(pfind+1,','); //ignoring navigation receiver warning
			pfind = strchr(pfind+1,',');
			{			
				char temp[3];
				strncpy(temp,pfind+1,2);
 				lat = atof(temp);
				strncpy(temp,pfind+3,2);
				lat = lat + (atof(temp)/60);
				strncpy(temp,pfind+6,2);
				lat = lat + (atof(temp)/3600);
				pfind = strchr(pfind+1,',');
				if(pfind[1] == 'S'){lat = lat * -1;} 
			} 

			// Extract and convert longitude
			pfind = strchr(pfind+1,',');
			{						
				char temp[3];
				strncpy(temp,pfind+1,2);
 				lon = atof(temp);
				strncpy(temp,pfind+3,2);
				lon = lon + (atof(temp)/60);
				strncpy(temp,pfind+6,2);
				lon = lon + (atof(temp)/3600);
				pfind = strchr(pfind+1,',');	
				if(pfind[1] == 'W'){lon = lon * -1;}
			} 

			// Dump to file
			pOutput = fopen("output","a");
			if(pOutput == NULL)
			{
				printf("I am here");
				return -1;
			}
			fprintf(pOutput,"%s, %f, %f \n", UTC, lat, lon);
			fclose(pOutput);
		}else if((input[0] == 'q'))
		{
			break;
		}
	}

	return 0;
}

