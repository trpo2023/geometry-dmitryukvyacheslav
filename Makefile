CFLAGS = -Wall -Wextra -Werror -I./src
CPPFLAGS = -MMD
.PHONY: clean
bin/geometry: ./obj/src/geometry/main.o ./obj/src/libgeometry/libgeometry.a
	$(CC) $(CFLAGS) -o $@ $^ 

./obj/src/geometry/main.o: ./src/geometry/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 

./obj/src/libgeometry/libgeometry.a: ./obj/src/libgeometry/shapes.o
	ar rcs $@ $^

./obj/src/libgeometry/shapes.o: ./src/libgeometry/shapes.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $< 

clean:
	rm -rf ./obj/src/geometry/*.d ./obj/src/geometry/*.o ./obj/src/libgeometry/*.d ./obj/src/libgeometry/*.a ./obj/src/libgeometry/*.o  ./bin/geometry
-include main.d geometry.d