#  CITS2002 Project 2 2022
#  Student:   23006364   HU   ZHUO   100

V1.0 = ./v1.0
V2.0 = ./v2.0

MAKE = make
MOVE = mv ./trove ../

# default make v1.0
trove: 1.0

1.0: 	$(V1.0) makefile
	cd $(V1.0) && $(MAKE) && $(MOVE)

2.0: 	$(V2.0) makefile	
	cd $(V2.0) && $(MAKE) && $(MOVE)

clean:
	rm -f trove