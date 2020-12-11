day%.out: out/types.o misc/main.cpp days/day%.cpp
	g++-10 -std=c++2a $(flags) -Dcurrent_day=$(@:.out=) days/$(@:out=cpp) misc/main.cpp out/types.o -o $@

day%_test.out: out/types.o misc/main_test.cpp days/day%.cpp
	g++-10 -std=c++2a $(flags) -DTEST_BUILD -Dcurrent_day=$(@:_test.out=) days/$(@:_test.out=.cpp) misc/main_test.cpp out/types.o -o $@

days/day%.cpp:
	cp 'misc/day.cpp.template' $@
	sed -i -e "s/current_day/$(shell basename $@ | cut -f 1 -d '.')/g" $@

out/types.o: misc/types.hpp misc/types.cpp
	mkdir -p out/
	g++-10 -std=c++2a $(flags) -c misc/types.cpp -o $@

.PHONY: clean
clean:
	rm out/* day*.out day*.output
