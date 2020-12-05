day1.out: out/types.o day1.cpp
	g++-10 -std=c++2a $(flags) day1.cpp out/types.o -o $@

day2.out: out/types.o day2.cpp
	g++-10 -std=c++2a $(flags) day2.cpp out/types.o -o $@

day3.out: out/types.o day3.cpp
	g++-10 -std=c++2a $(flags) day3.cpp out/types.o -o $@

day4.out: out/types.o day4.cpp
	g++-10 -std=c++2a $(flags) day4.cpp out/types.o -o $@

day5.out: out/types.o day5.cpp
	g++-10 -std=c++2a $(flags) day5.cpp out/types.o -o $@

out/types.o: types.hpp types.cpp
	mkdir -p out/
	g++-10 -std=c++2a $(flags) -c types.cpp -o $@

.PHONY: clean
clean:
	rm out/* day*.out day*.output
