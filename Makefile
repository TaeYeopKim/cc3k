CXX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -g
OBJECTS=main.o controller.o view.o map.o cell.o chamber.o gold.o object.o potion.o enemy.o player.o cellCorFactory.o enemyFactory.o goldFactory.o playerFactory.o potionFactory.o stair.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm *.o ${EXEC}
