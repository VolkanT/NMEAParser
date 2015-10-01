Standard usage:
1) execute make to compile source.
2) execute ./NMEAParse to run the application. 
3) after the "stream content" prompt, paste in data. 
4) parser is looking for NMEA GPRMC sentence header, all content that does not have a GPRMC header is ignored. All content that does have a valid header will be visible in decimal format on a file titled "output". The output file is located within the project folder.   
5) type 'q' when finished with application.

Piping: 
If you wish to see an example of piping to the application then run "head -300 testdata | ./NMEAParse" this will pipe the 300 lines of NMEA data available within testdata to the application.

Testing
Test data which includes GPRMC, GPGGA, and GPGLL sentences were randomly generated at "freenmea.net/emitter". In total there are 300 sentences, with 100 sentences of each mentioned format.   

This test can be run by executing "make test"
