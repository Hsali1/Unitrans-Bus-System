# Makefile for f2022, ecs36b
#
# g++ -std=c++14 test_GPS.cpp GPS.cpp -o test_GPS
#
# example: $ ./test_GPS 48.88 2.3

CC 	= g++ -std=c++14
CFLAGS 	= -g -I/usr/include/jsoncpp
LDFLAGS = -L/opt/homebrew/lib -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -lcurl -ljsonrpccpp-client

INC	=	ecs36b_Common.h # Hassan change

# rules.
all: 	test_ThingPerson ecs36b_hw6_driver

#
#

Record.o:	Record.cpp Record.h
	$(CC) -c $(CFLAGS) Record.cpp

GPS.o:		GPS.cpp GPS.h
	$(CC) -c $(CFLAGS) GPS.cpp

JvTime.o:	JvTime.cpp JvTime.h
	$(CC) -c $(CFLAGS) JvTime.cpp

JhTime.o:	JhTime.cpp JhTime.h
	$(CC) -c $(CFLAGS) JhTime.cpp

Person.o:	Person.cpp Person.h
	$(CC) -c $(CFLAGS) Person.cpp

Thing.o:	Thing.cpp Thing.h
	$(CC) -c $(CFLAGS) Thing.cpp

ecs36b_JSON.o:		ecs36b_JSON.cpp $(INC) # Hassan 
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp
# Hassan change end

test_ThingPerson.o:	test_ThingPerson.cpp GPS.h Thing.h Person.h JvTime.h Record.h JhTime.h
	$(CC) -c $(CFLAGS) test_ThingPerson.cpp

test_ThingPerson:	GPS.o test_ThingPerson.o Thing.o Person.o JvTime.o Record.o JhTime.o ecs36b_JSON.o
	g++ -std=c++14 test_ThingPerson.o GPS.o Thing.o Person.o JvTime.o Record.o JhTime.o ecs36b_JSON.o -o test_ThingPerson $(LDFLAGS)

ecs36b_hw6_driver.o:	ecs36b_hw6_driver.cpp GPS.h Thing.h Person.h JvTime.h Record.h JhTime.h
	$(CC) -c $(CFLAGS) ecs36b_hw6_driver.cpp

ecs36b_hw6_driver:	GPS.o ecs36b_hw6_driver.o Thing.o Person.o JvTime.o Record.o JhTime.o ecs36b_JSON.o
	g++ -std=c++14 ecs36b_hw6_driver.o GPS.o Thing.o Person.o JvTime.o Record.o JhTime.o ecs36b_JSON.o -o ecs36b_hw6_driver $(LDFLAGS)

clean:
	rm -f *.o *~ core test_ThingPerson ecs36b_hw6_driver

