.PHONY: all install clean

.DEFAULT_GOAL:= all

config ?= debug
CXX_FLAGS:=-Wall

INCLUDES:=-Isrc $(BOOST_CGI_INC) $(BOOST_INC)

LD_FLAGS:=-z muldefs $(BOOST_LIB_DIR)
LIBS:=-lboost_system -lboost_filesystem

build_dir=build
config_dir=$(build_dir)/$(config)
objs_dir=$(config_dir)/objs

$(build_dir):
	mkdir -p $@

$(config_dir):
	mkdir -p $@

$(objs_dir):
	mkdir -p $@


###### library

lib_target = libcppWF.so
lib_srcs_dir = src
lib_srcs:=$(foreach dir,$(lib_srcs_dir), $(wildcard $(dir)/*.cpp))
lib_artifact=$(build_dir)/$(config)/$(lib_target)
lib_install_dest=web/lib/$(lib_target)

lib_objs:= $(lib_srcs:%.cpp=$(objs_dir)/%.o)
lib_objs_subdirs:=$(sort $(dir $(lib_objs)))


$(lib_objs_subdirs):
	mkdir -p $@

###### executable

exe_target = cppWF
exe_srcs_dir = examples
exe_srcs:=$(foreach dir,$(exe_srcs_dir), $(wildcard $(dir)/*.cpp))
exe_artifact=$(build_dir)/$(config)/$(exe_target)
exe_install_dest=web/public/$(exe_target)

exe_objs:= $(exe_srcs:%.cpp=$(objs_dir)/%.o)
exe_objs_subdirs:=$(sort $(dir $(exe_objs)))

$(exe_objs_subdirs):
	mkdir -p $@

###### common

all: install

install: $(lib_install_dest) $(exe_install_dest)

$(lib_install_dest) : $(lib_artifact)
	rm -f $@
	cp $< $@

$(exe_install_dest) : $(exe_artifact)
	rm -f $@
	cp $< $@
	
$(lib_artifact): $(objs_dir) $(lib_objs_subdirs) $(lib_objs)
	$(CXX) $(lib_objs) -shared -o $@ $(LD_FLAGS)

$(exe_artifact): $(objs_dir) $(exe_objs_subdirs) $(exe_objs) $(lib_artifact)
	$(CXX) $(exe_objs) -o $@ $(LD_FLAGS) $(LIBS) -L$(build_dir)/$(config) -lcppWF

$(objs_dir)/%.o : %.cpp
	$(CXX) -c $< -o $@ $(CXX_FLAGS) $(INCLUDES) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$@"

clean:
	rm -f $(exe_artifact)
	rm -f $(lib_artifact)
	rm -fr $(objs_dir)
	rm -fr $(config_dir)
	rm -fr $(build_dir)

-include $(foreach obj,$(exe_objs), $(obj:%.o=%.d))
