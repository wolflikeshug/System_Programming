estimatecron : estimatecron.c
	gcc -o estimatecron estimatecron.c
	./estimatecron sep crontab-file estimate-file
	./estimatecron dec crontab-file estimate-file
	./estimatecron 0 crontab-file estimate-file
	./estimatecron 11 crontab-file estimate-file
	./estimatecron 1 crontab-file estimate-file
	./estimatecron jan crontab-file estimate-file

clean :
	rm -f estimatecron
