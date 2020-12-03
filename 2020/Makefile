day1.out: out/types.o day1.cpp day1.input
	g++ $(flags) day1.cpp out/types.o -o $@

day2.out: out/types.o day2.cpp day2.input
	g++ $(flags) day2.cpp out/types.o -o $@

day3.out: out/types.o day3.cpp day3.input
	g++ $(flags) day3.cpp out/types.o -o $@

out/types.o: types.hpp types.cpp
	mkdir -p out/
	g++ $(flags) -c types.cpp -o $@

.PHONY: clean
clean:
	rm out/* day*.out
