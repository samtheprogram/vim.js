### Vim.js : JavaScript port of Vim

by Tinmarino 

### See demo there


### Compile
The EXPORTED_FUNCTIONS must be setted in emscripten/src/setting.js

var EXPORTED_FUNCTIONS = [ '_main',
'_input_available',
'_gui_web_handle_key',
'_gui_send_mouse_event',
'_gui_mouse_moved',
];




# Old readme by Lu Wang


A Tool/Toy for Non-Beginners

by Lu Wang

### [Try it online](http://coolwanglu.github.io/vim.js/emterpreter/vim.html)

### Variations
- [NW.js](https://github.com/coolwanglu/vim.js/tree/master/NW.js)
- [Firefox extension](https://addons.mozilla.org/en-US/firefox/addon/vimjs-extension/)
- [Asyncify](http://coolwanglu.github.io/vim.js/asyncify/vim.html)
- [Streamline.js](http://coolwanglu.github.io/vim.js/streamlinejs/vim.html)

Recommended browsers: Firefox, Chrome, IE


### Vim.js Features

- ASM.js enabled
- Persistent `~/.vimrc`
- Execute JavaScript from Vim.js 
- Read local files 
- Read files from Dropbox

Run `:e $VIM/vimrc` for more detail.



### Vim Features

The online demo is built with the small feature set (`--with-features=small`), 
with also a few from the normal set.
Run `:version` to check details. 
(`--with-features=normal` is too large and too slow for online usage.)

Some features can be requested via pull requests, some are not intended to be included. 
Please discuss with me first before you work on a PR.



### Tips for hackers

- Need emscripten with ASYNCIFY enabled
- Need GCC & cproto (maybe) &mdash; Sometimes you need to run `make proto` when you see errors about 'undeclared variables/functions/structs' or '***.pro' file not found
- Read `build.sh`
- The building process might take lots of memory



### Contact

Lu Wang coolwanglu(a)gmail.com &mdash; please do not expect a prompt response.



### License

Read `LICENSE`



