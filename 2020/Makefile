day%.out: out/types.o day%.cpp
	g++-10 -std=c++2a $(flags) $(@:out=cpp) out/types.o -o $@

day%.cpp:
	cp template.cpp $@

out/types.o: types.hpp types.cpp
	mkdir -p out/
	g++-10 -std=c++2a $(flags) -c types.cpp -o $@

.PHONY: clean
clean:
	rm out/* day*.out day*.output
