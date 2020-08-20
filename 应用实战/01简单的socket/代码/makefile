all:code01 code02 code03 code04 code05 code07 code06 code10 code11

code11:code11.cpp
	g++ -o code11 code11.cpp

code10:code10.cpp
	g++ -o code10 code10.cpp

code06:code06.cpp
	g++ -o code06 code06.cpp

code07:code07.cpp
	g++ -o code07 code07.cpp -pthread

code05:code05.cpp
	g++ -o code05 code05.cpp

code04:code04.cpp myhead.cpp myhead.h
	g++ -o code04 code04.cpp myhead.cpp

code03:code03.cpp myhead.cpp myhead.h
	g++ -o code03 code03.cpp myhead.cpp

code01:code01.cpp
	g++ -o code01 code01.cpp

code02:code02.cpp
	g++ -o code02 code02.cpp

clean:
	rm -f code01 code02 code03 code04 code05 code07 code06
