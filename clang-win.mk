CC = clang
CXX = clang++
CFLAGS = -O2 -std=c89 -pedantic
CXXFLAGS = -O2 -std=c++14 -pedantic
LFLAGS =
OBJSBASIC = wavdump.exe wav_write.exe
OBJSFLTRC = wav_can_filt.exe wav_reverb.exe wav_flanger.exe
OBJSFLTRCPP = wavCanFilt.exe wavReverb.exe wavFlanger.exe
OBJS = $(OBJSBASIC) $(OBJSFLTRC) $(OBJSFLTRCPP)

all: $(OBJS)

wavCanFilt.exe: wavCanFilt.o wave.o CanonicalFilter.o
	$(CXX) -o $@ $^ $(LFLAGS)
wavReverb.exe: wavReverb.o wave.o CircularFilter.o
	$(CXX) -o $@ $^ $(LFLAGS)
wavFlanger.exe: wavFlanger.o wave.o FlangerFilter.o FractionalDelay.o
	$(CXX) -o $@ $^ $(LFLAGS)

wavCanFilt.o: wavCanFilt.cpp Wave.hpp CanonicalFilter.h
	$(CXX) $(CXXFLAGS) -c $<
wavReverb.o: wavReverb.cpp Wave.hpp CircularFilter.h
	$(CXX) $(CXXFLAGS) -c $<
wavFlanger.o: wavFlanger.cpp Wave.hpp FlangerFilter.h
	$(CXX) $(CXXFLAGS) -c $<

CanonicalFilter.o: CanonicalFilter.cpp CanonicalFilter.h
	$(CXX) $(CXXFLAGS) -c $<
CircularFilter.o: CircularFilter.cpp CircularFilter.h
	$(CXX) $(CXXFLAGS) -c $<
FractionalDelay.o: FractionalDelay.cpp FractionalDelay.h
	$(CXX) $(CXXFLAGS) -c $<
FlangerFilter.o: FlangerFilter.cpp FlangerFilter.h FractionalDelay.h
	$(CXX) $(CXXFLAGS) -c $<

wav_flanger.exe: wav_flanger.o wave.o fractional_delay.o
	$(CC) -o $@ $^ $(LFLAGS)
wav_can_filt.exe: wav_can_filt.o wave.o canonical_filter.o
	$(CC) -o $@ $^ $(LFLAGS)
wav_reverb.exe: wav_reverb.o wave.o circular_filter.o
	$(CC) -o $@ $^ $(LFLAGS)

wav_flanger.o: wav_flanger.c wave.h fractional_delay.h
	$(CC) $(CFLAGS) -c $<
wav_can_filt.o: wav_can_filt.c wave.h canonical_filter.h
	$(CC) $(CFLAGS) -c $<
wav_reverb.o: wav_reverb.c wave.h circular_filter.h
	$(CC) $(CFLAGS) -c $<

fractional_delay.o: fractional_delay.c fractional_delay.h
	$(CC) $(CFLAGS) -c $<
canonical_filter.o: canonical_filter.c canonical_filter.h
	$(CC) $(CFLAGS) -c $<
circular_filter.o: circular_filter.c circular_filter.h
	$(CC) $(CFLAGS) -c $<

wav_write.exe: wav_write.o wave.o
	$(CC) -o $@ $^ $(LFLAGS)
wavdump.exe: wavdump.o wave.o
	$(CC) -o $@ $^ $(LFLAGS)

wav_write.o: wav_write.c wave.h
	$(CC) $(CFLAGS) -c $<
wavdump.o: wavdump.c wave.h
	$(CC) $(CFLAGS) -c $<

wave.o: wave.c wave.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(OBJS)
