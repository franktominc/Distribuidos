COMP=gcc
programa=ring
	
all: $(programa)

$(programa): $(programa).o smpl.o rand.o
	$(COMP) -o $@ -Bstatic $(programa).o smpl.o rand.o -lm -fPIC

smpl.o: smpl.c smpl.h
	$(COMP) -c smpl.c -fPIC

$(programa).o: $(programa).c smpl.h
	$(COMP) -c  $(programa).c -fPIC

rand.o: rand.c
	$(COMP) -c rand.c -fPIC

clean:
	$(RM) $(programa).o $(programa) 
 
