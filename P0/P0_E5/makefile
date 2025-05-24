CC = gcc -Wall

HEADER_FILES_DIR = .

INCLUDES = -I $(HEADER_FILES_DIR)

OUTPUT = P0_E5
LIB_HEADERS = $(HEADER_FILES_DIR)/operaciones.h

SRCS = main.c sqrt.c 
OBJS = $(SRCS:.c=.o)

$(OUTPUT) : $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS)

%.o : %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall : clean
	rm -f $(OUTPUT)
clean:
	rm -f *.o *~