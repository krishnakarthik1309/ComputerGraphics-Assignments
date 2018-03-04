compile:
	g++ *.cpp -lGLEW -lGL -lGLU -lglut -lIL -o run

submit:
	mkdir krishna_14292
	cp -r *.h *.md shaders/ textures/ *.cpp Makefile krishna_14292/
	zip -r -q krishna_14292.zip krishna_14292/
	rm -r krishna_14292/

clean:
	rm run

deep_clean:
	rm run
	rm krishna_14292.zip