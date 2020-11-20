CC = gcc
CXX = g++
CFLAGS = -O2 -std=c89 -pedantic -Wall
CXXFLAGS = -g -O2 -std=c++11 -pedantic -Wall
LFLAGS =
OBJSBASIC = wavdump.exe wavwrite.exe
OBJSFLTRC = wavcanfltr.exe wav_reverb.exe wav_flanger.exe
OBJSFLTRCPP = wavdir1.exe wavdir2.exe wavdir2t.exe wavbiquad.exe wavReverb.exe wavFlanger.exe
OBJS = $(OBJSBASIC) $(OBJSFLTRC) $(OBJSFLTRCPP)

all: $(OBJS)

wavdir1.exe: wavdir1.cpp wave.o directform.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavdir2.exe: wavdir2.cpp wave.o directform.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavdir2t.exe: wavdir2t.cpp wave.o directform.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavbiquad.exe: wavbiquad.cpp wave.o biquad.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavReverb.exe: wavReverb.cpp wave.o circular.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavFlanger.exe: wavFlanger.cpp wave.o delay.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lm $(LFLAGS)

directform.o: directform.cpp directform.h
	$(CXX) $(CXXFLAGS) -c $<
biquad.o: biquad.cpp biquad.h
	$(CXX) $(CXXFLAGS) -c $<
circular.o: circular.cpp circular.h
	$(CXX) $(CXXFLAGS) -c $<
delay.o: delay.cpp delay.h
	$(CXX) $(CXXFLAGS) -c $<

wavcanfltr.exe: wavcanfltr.o wave.o canfltr.o
	$(CC) -o $@ $^ $(LFLAGS)
wav_flanger.exe: wav_flanger.o wave.o delayline.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wav_reverb.exe: wav_reverb.o wave.o cirfltr.o
	$(CC) -o $@ $^ $(LFLAGS)

wavcanfltr.o: wavcanfltr.c wave.h canfltr.h
	$(CC) $(CFLAGS) -c $<
wav_flanger.o: wav_flanger.c wave.h delayline.h
	$(CC) $(CFLAGS) -c $<
wav_reverb.o: wav_reverb.c wave.h cirfltr.h
	$(CC) $(CFLAGS) -c $<

delayline.o: delayline.c delayline.h
	$(CC) $(CFLAGS) -c $<
canfltr.o: canfltr.c canfltr.h
	$(CC) $(CFLAGS) -c $<
cirfltr.o: cirfltr.c cirfltr.h
	$(CC) $(CFLAGS) -c $<

wavwrite.exe: wavwrite.o wave.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wavdump.exe: wavdump.o wave.o
	$(CC) -o $@ $^ $(LFLAGS)

wavwrite.o: wavwrite.c wave.h
	$(CC) $(CFLAGS) -c $<
wavdump.o: wavdump.c wave.h
	$(CC) $(CFLAGS) -c $<

wave.o: wave.c wave.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(OBJS)
