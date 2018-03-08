CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -std=c++11

OBJS =		SimpleMySQL.o

LIBS = 		-L/usr/lib -lmysqlcppconn

TARGET =	SimpleMySQL

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
