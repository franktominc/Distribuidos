COMP=gcc
programa=ring
	
all: $(programa)

$(programa): $(programa).o smpl.o rand.o
	$(COMP) -o $@ -Bstatic $(programa).o smpl.o rand.o -lm -fPIC

smpl.o: smpl.c smpl.h
	$(COMP) -c smpl.c

$(programa).o: $(programa).c smpl.h
	$(COMP) -c  $(programa).c

rand.o: rand.c
	$(COMP) -c rand.c

clean:
	$(RM) $(programa).o $(programa)
 
