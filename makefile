CC = gcc
CFLAGS = -Wall
PTHREAD = -pthread

TARGET = multiThreadSorter_thread
TARGET2 = mergesort
RM = rm

all: $(TARGET) $(TARGET2)

$(TARGET): $(TARGET).c ; $(CC) $(PTHREAD) $(CFLAGS) -o $(TARGET) $(TARGET).c $(TARGET2).c
    
$(TARGET2): $(TARGET2).c ; $(CC) $(PTHREAD) $(CFLAGS) -c $(TARGET2).c
    
clean: ; $(RM) $(TARGET) ; $(RM) $(TARGET2).o
