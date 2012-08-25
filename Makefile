.PHONY: all install

.DEFAULT_GOAL:= all

config ?= debug
target = cppWF

build_dir=build
config_dir=$(build_dir)/$(config)
objs_dir=$(config_dir)/objs
artifact=$(build_dir)/$(config)/$(target)

install_dest=web/public/$(target)

$(build_dir):
	mkdir $@

$(config_dir): $(build_dir)
	mkdir $@

$(objs_dir): $(config_dir)
	mkdir $@

all: install

install: $(install_dest)

$(install_dest) : $(artifact)
	rm -f $(install_dest)
	cp $(artifact) $(install_dest)
	
$(artifact): $(objs_dir)
	touch $@

clean:
	rm -f $(artifact)
	rm -fr $(objs_dir)
	rm -fr $(config_dir)
	rm -fr $(build_dir)
