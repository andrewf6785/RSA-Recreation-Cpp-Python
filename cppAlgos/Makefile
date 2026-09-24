CXX = g++
CXXFLAGS = -O2

SOURCES = bigInt/bigInt.cpp randomNumberGenerator/randomNumberGenerator.cpp decrypt.cpp demo.cpp eea.cpp encrypt.cpp keys.cpp miller_rabin.cpp modexp.cpp pickPrime.cpp commonPrimeCheck.cpp montgomeryConstant.cpp montgomeryModularExpo.cpp montgomeryReduction.cpp
OBJECTS = $(SOURCES:.cpp=.o)

m: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o m $(OBJECTS)

.PHONY: clean
clean:
	rm -f $(OBJECTS) m m.exe