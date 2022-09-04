all: gnu clang vcpp icl

gnu:
	g++ -c encoding/imp/iso8859.cpp -o obj/iso8859.o
	g++ -c encoding/imp/oem.cpp -o obj/oem.o
	g++ -c encoding/imp/windows.cpp -o obj/windows.o
	ar rvs bin/charset-g++.a obj/iso8859.o obj/oem.o obj/windows.o

clang:
	clang -c encoding/imp/iso8859.cpp -o obj/iso8859.o
	clang -c encoding/imp/oem.cpp -o obj/oem.o
	clang -c encoding/imp/windows.cpp -o obj/windows.o
	llvm-ar rvs bin/charset-clang.a obj/iso8859.o obj/oem.o obj/windows.o

vcpp:
	cl /c encoding/imp/iso8859.cpp /Fo.\obj\iso8859.obj
	cl /c encoding/imp/oem.cpp /Fo.\obj\oem.obj
	cl /c encoding/imp/windows.cpp /Fo.\obj\windows.obj
	lib /OUT:bin/charset-vc++.lib obj/iso8859.obj obj/oem.obj obj/windows.obj

icl:
	icl /c encoding/imp/iso8859.cpp /Fo.\obj\iso8859.obj
	icl /c encoding/imp/oem.cpp /Fo.\obj\oem.obj
	icl /c encoding/imp/windows.cpp /Fo.\obj\windows.obj
	xilib -lib /OUT:bin/charset-icl.lib obj/iso8859.obj obj/oem.obj obj/windows.obj
