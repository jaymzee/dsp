CC = gcc
CXX = g++
CFLAGS = -O2 -std=c89 -pedantic -Wall
CXXFLAGS = -g -O2 -std=c++11 -pedantic -Wall
LFLAGS =
OBJSBASIC = wavdump wav_write
OBJSFLTRC = wav_can_filt wav_reverb wav_flanger
OBJSFLTRCPP = wavDirFrm1 wavDirFrm2 wavDirFrm2T wavBiQuad wavReverb wavFlanger
OBJS = $(OBJSBASIC) $(OBJSFLTRC) $(OBJSFLTRCPP)

all: $(OBJS)

wavDirFrm1: wavDirFrm1.cpp wave.o DirectFormFilter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavDirFrm2: wavDirFrm2.cpp wave.o DirectFormFilter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavDirFrm2T: wavDirFrm2T.cpp wave.o DirectFormFilter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavBiQuad: wavBiQuad.cpp wave.o BiQuadFilter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavReverb: wavReverb.cpp wave.o CircularFilter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)
wavFlanger: wavFlanger.cpp wave.o FractionalDelay.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lm $(LFLAGS)

DirectFormFilter.o: DirectFormFilter.cpp DirectFormFilter.h
	$(CXX) $(CXXFLAGS) -c $<
BiQuadFilter.o: BiQuadFilter.cpp BiQuadFilter.h
	$(CXX) $(CXXFLAGS) -c $<
CircularFilter.o: CircularFilter.cpp CircularFilter.h
	$(CXX) $(CXXFLAGS) -c $<
FractionalDelay.o: FractionalDelay.cpp FractionalDelay.h
	$(CXX) $(CXXFLAGS) -c $<

wav_flanger: wav_flanger.o wave.o fractional_delay.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wav_can_filt: wav_can_filt.o wave.o canonical_filter.o
	$(CC) -o $@ $^ $(LFLAGS)
wav_reverb: wav_reverb.o wave.o circular_filter.o
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

wav_write: wav_write.o wave.o
	$(CC) -o $@ $^ -lm $(LFLAGS)
wavdump: wavdump.o wave.o
	$(CC) -o $@ $^ $(LFLAGS)

wav_write.o: wav_write.c wave.h
	$(CC) $(CFLAGS) -c $<
wavdump.o: wavdump.c wave.h
	$(CC) $(CFLAGS) -c $<

wave.o: wave.c wave.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(OBJS)
