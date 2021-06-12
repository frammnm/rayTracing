PROG=ogl
SRCS= \
main.cc \
obj.cc \
vect3.cc \
ray.cc \
sphere.cc \
hittable.cc \
hittable_list.cc \
camera.cc \
png.cc 

#world.cc

CXX:=g++
CXXFLAGS:=-O3 -march=native

# LIBS:=-lglfw -lpng -lGLEW -lGLU -lGL
LIBS:= -lglfw3 -lglew32 -lglu32 -lopengl32 -lgdi32 -lpng -lz

OBJS:=$(SRCS:.cc=.o)
DEPS:=$(SRCS:.cc=.d)

all: $(PROG)

$(PROG): $(OBJS)
	@echo LD $<
	@$(CXX) -o $@ $^ $(LIBS)

%.o: %.cc
	@echo CXX $<
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	@if [ -n "$(OBJS)" ]; then rm -f $(OBJS); fi
	@if [ -n "$(DEPS)" ]; then rm -f $(DEPS); fi
	@if [ -f core ]; then rm -f core; fi
	@rm -f tags *.linkinfo
	@rm -f *.png

mrproper:
	@if [ -n "$(PROG)" ]; then rm -f $(PROG); fi
	@if [ -n "$(OBJS)" ]; then rm -f $(OBJS); fi
	@if [ -n "$(DEPS)" ]; then rm -f $(DEPS); fi
	@if [ -f core ]; then rm -f core; fi
	@rm -f tags *.linkinfo

-include $(DEPS)