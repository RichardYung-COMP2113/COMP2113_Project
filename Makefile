all: sonar.cpp
	g++ -o sonar sonar.cpp
clean:
	rm sonar
