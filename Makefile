.PHONY: all install clean

.DEFAULT_GOAL:= all

config ?= debug
target = cppWF
srcs_dir = src

INCLUDES:=-I$(BOOST_CGI_INC) $(BOOST_INC)

LD_FLAGS:=-z muldefs $(BOOST_LIB_DIR)
LIBS:=-lboost_system -lboost_filesystem

srcs:=$(wildcard $(srcs_dir)/*.cpp)

build_dir=build
config_dir=$(build_dir)/$(config)
objs_dir=$(config_dir)/objs
artifact=$(build_dir)/$(config)/$(target)

install_dest=web/public/$(target)

objs:= $(srcs:%.cpp=$(objs_dir)/%.o)
objs_subdirs:=$(sort $(dir $(objs)))

$(build_dir):
	mkdir -p $@

$(config_dir):
	mkdir -p $@

$(objs_dir):
	mkdir -p $@

$(objs_subdirs):
	mkdir -p $@

all: install

install: $(install_dest)

$(install_dest) : $(artifact)
	rm -f $@
	cp $< $@
	
$(artifact): $(objs_dir) $(objs_subdirs) $(objs)
	$(CXX) $(objs) -o $@ $(LD_FLAGS) $(LIBS)

$(objs_dir)/%.o : %.cpp
	$(CXX) -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(artifact)
	rm -fr $(objs_dir)
	rm -fr $(config_dir)
	rm -fr $(build_dir)
