pa13: pa13b.o
	$(CXX) $(CXXFLAGS) pa13b.o -o pa13b

pa13b.o: pa13b.cpp Container.hpp
	$(CXX) $(CXXFLAGS) pa13b.cpp -c

clean:
	rm -f Container.o pa13b.o pa13b

turnin:
	turnin -c cs202 -p pa13b -v Container.hpp pa13b.cpp Makefile
