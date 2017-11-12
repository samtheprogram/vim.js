#!/bin/bash


export CPPFLAGS="-DFEAT_GUI_WEB"

export CPP="gcc -E "

export CFLAGS="-g -Wall -Wmissing-prototypes -O0 \
	-s LINKABLE=1 s EXPORT_ALL=1 \
    -s EXPORTED_FUNCTIONS=['_main_','_input_available','_gui_web_handle_key','_gui_send_mouse_event','_gui_mouse_move'] \
"

VIMDIR="/vim"

do_proto(){
emmake make proto
}

do_config() {
    echo config
emconfigure ./configure \
    --enable-gui=web \
    --prefix=$VIMDIR \
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
    --with-local-dir="/" \
    --disable-smack \
    --disable-channel \
    --with-compiledby="Tinmarino" 
}

do_make() {
emmake make VIMRUNTIMEDIR=$VIMDIR
}

do_link() {
pushd web
cp ../src/vim vim.bc

emcc  \
    --js-library vim_lib.js \
    -O2 \
    --closure 0 \
    -s EMTERPRETIFY=1 \
    -s EMTERPRETIFY_ASYNC=1 \
    -s 'EMTERPRETIFY_FILE="vimjs.dat"' \
    --memory-init-file 1 \
    vim.bc \
    -o vim.js 

popd
}

    #-s 'EMTERPRETIFY_FILE="vimjs.dat"' \
    #-s EXPORTED_FUNCTIONS="['_main','_input_available','_gui_web_handle_key','_gui_send_mouse_event','_gui_mouse_move']" \
	#-s EMTERPRETIFY_FILE=\"vim_bytecode.bin\" \
	#--prefix="."
#emcc vim.bc \
#    -o vim.js \
#    -Oz \
#    --js-library vim_lib.js \
#    --embed-file usr \



do_transform() {
pushd web

mv vim.js vim-1.js

# vim-2._js is counted as a job
JOB_COUNT=$((JOB_COUNT-1))

echo "Transfoming..."
node transform.js vim-1.js vim-2 $JOB_COUNT

echo "Compiling with streamline.js..."
_node -li -c vim-2._js &
for ((i=0; i < JOB_COUNT; i++))
do
    _node -li -c vim-2.$i._js &
done
wait

for ((i=0; i < JOB_COUNT; i++))
do
    cat vim-2.$i.js >> vim-2.js
done

popd
}

do_compress() {
pushd web 

echo "Optimizing with closure compiler"
export EM_DIR="/home2/tourneboeuf/Software/Js/EmSdk/emscripten/1.37.22"
#--compilation_level ADVANCED_OPTIMIZATIONS \
java -Xmx2048m \
     -jar $EM_DIR/third_party/closure-compiler/compiler.jar \
     --language_in ECMASCRIPT5 \
     --js vim-2.js\
     --js_output_file vim.js \

popd
}


do_copy() {
cp web/vim.js NW.js/
cp web/vim.js.mem NW.js/
}
# vim: expandtab: 
