#!/bin/bash
do_config() {
    echo config
# something wrong with emcc + cproto, use gcc as CPP instead
CPPFLAGS="-Os -DFEAT_GUI_WEB" \
CPP="gcc -E" \
# CPPCLAGS
# LDFLAGS 
# CC      -> /usr/share/emscripten/emcc

/usr/bin/emconfigure ./configure \
    --enable-gui=web \
    --with-features=small \
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
    --disable-sniff \
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
emmake make -j8
}

do_link() {
pushd web
cp ../src/vim vim.bc

OPT_ASYNCIFY="-s ASYNCIFY=1 \
    -s EXPORTED_FUNCTIONS=\"['_main', '_input_available', '_gui_web_handle_key']\" \
    -s ASYNCIFY_FUNCTIONS=\"['emscripten_sleep', 'vimjs_flash', 'vimjs_browse']\" "

OPT_EMTERPRETER="-s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1"


# Use vim.js as filename to generate vim.js.mem
emcc vim.bc \
    -o vim.js \
    --js-library vim_lib.js \
    --embed-file usr \

popd
}

do_copy() {
cp web/vim.js NW.js/
cp web/vim.js.mem NW.js/
}

#do_config
#do_make
do_link
#do_copy
