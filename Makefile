TARGET = psf

$(TARGET): clean main.c PSform.c
	gcc -o $(TARGET) main.c PSform.c

clean:
	rm -f $(TARGET)
