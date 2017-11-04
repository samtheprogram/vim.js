#!/bin/bash


export CPPFLAGS=" \
	-DFEAT_MBYTE \
	-DFEAT_GUI_WEB" 

export CPP="gcc -E "

export CFLAGS="-g -Wall -Wmissing-prototypes -O0 \
	-s LINKABLE=1 s EXPORT_ALL=1 "

VIMDIR="/vim"

do_proto(){
emmake make proto
}

do_config() {
    echo config
emconfigure ./configure \
    --enable-gui=web \
    --prefix=$VIMDIR \
    --with-features=big \
    --disable-selinux \
    --disable-xsmp \
    --disable-xsmp-interact \
    --disable-luainterp \
    --disable-mzschemeinterp \
    --disable-perlinterp \
    --disable-pythoninterp \
    --disable-python3interp \
    --disable-tclinterp \
    --disable-rubyinterp \
    --disable-cscope \
    --disable-workshop \
    --disable-netbeans \
    --disable-multibyte \
    --disable-hangulinput \
    --disable-xim \
    --disable-fontset \
    --disable-gtk2-check \
    --disable-gnome-check \
    --disable-motif-check \
    --disable-athena-check \
    --disable-nextaw-check \
    --disable-carbon-check \
    --disable-gtktest \
    --disable-largefile \
    --disable-acl \
    --disable-gpm \
    --disable-sysmouse \
    --disable-nls \
    --with-compiledby="Tinmarino" 
}

do_make() {
emmake make VIMRUNTIMEDIR=$VIMDIR
}

do_link() {
pushd web
cp ../src/vim vim.bc

emcc vim.bc \
    --js-library vim_lib.js \
    -Oz \
    --closure 0 \
    -s EMTERPRETIFY=1 \
    -s EMTERPRETIFY_ASYNC=1 \
    --memory-init-file 1 \
    -o vim.js 

popd
}

	#-s EMTERPRETIFY_FILE=\"vim_bytecode.bin\" \
	#--prefix="."
#emcc vim.bc \
#    -o vim.js \
#    -Oz \
#    --js-library vim_lib.js \
#    --embed-file usr \


do_copy() {
cp web/vim.js NW.js/
cp web/vim.js.mem NW.js/
}
# vim: expandtab: 
