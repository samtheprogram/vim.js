document.write('<script type="text/javascript" src="inc.js" ></script>')

// Prepare ground
function tin_init(){
    // Create path
    Module["FS_createPath"]("/", "vim", true, true);
    Module["FS_createPath"]("/vim", "plugin", true, true);
    Module["FS_createPath"]("/vim", "syntax", true, true);
    Module["FS_createPath"]("/vim", "colors", true, true);
    Module["FS_createPath"]("/vim", "txt", true, true);
    Module["FS_createPath"]("/vim/txt", "vimdoc", true, true);
    Module["FS_createPath"]("/vim/txt", "tindoc", true, true);
    Module["FS_createPath"]("/vim/txt", "cheatdoc", true, true);
    Module["FS_createPath"]("/vim/txt", "mess", true, true);

    // Load pages
    tin_load("/vim/first-page.txt");
    tin_load("/vim/goat1.txt");

    // Vimrc
    tin_load("/vim/vimrc");

    // Syntax
    tin_load("/vim/colors/Darkside.vim");
    tin_load("/vim/syntax/syntax.vim");
    tin_load("/vim/syntax/nosyntax.vim");
    tin_load("/vim/syntax/synload.vim");
    tin_load("/vim/syntax/myhelp.vim");
    tin_load("/vim/syntax/help.vim");
    tin_load("/vim/syntax/vim.vim");
    tin_load("/vim/syntax/sh.vim");
    tin_load("/vim/syntax/python.vim");

    // Index doc
    tin_url("/vim/txt/vimdoc/help.txt", "https://raw.githubusercontent.com/vim/vim/master/runtime/doc/help.txt");
    tin_load("/vim/txt/tindoc/meta-help.txt");
    tin_load("/vim/txt/cheatdoc/c-meta.txt");

    // Resize
    tin_full_screen();

}


// Define Module
var Module = {
  noInitialRun: false,
  noExitRuntime: true,
  arguments: ['vim/goat1.txt'],
  preRun: [ function() { vimjs.pre_run(); } ],
  postRun: [],
  print: function() {
    if (console.group !== undefined) {
      console.group.apply(console, arguments);
      console.groupEnd();
    } else {
      // IE
      console.log(arguments);
    }
  },
  printErr: function() {
    if (console.group !== undefined) {
      console.group.apply(console, arguments);
      console.groupEnd();
    } else {
      // IE
      console.log(arguments);
    }
  },
};

// Load dat
console.log(1, "OK 1");
var xhr = new XMLHttpRequest();
xhr.open('GET', 'vimjs.dat', true);
xhr.responseType = 'arraybuffer';
xhr.onload = function() {
  Module.emterpreterFile = xhr.response;
  var script = document.createElement('script');
  script.src = "vimjsdat.js";
  document.body.appendChild(script);
};
xhr.send();
console.log(1, "OK 2");




// Load init + save bugs
if(typeof Module==="undefined")
  Module=eval("(function() { try { return Module || {} } catch(e) { return {} } })()");
if(!Module.expectedDataFileDownloads){
	Module.expectedDataFileDownloads=0;
	Module.finishedDataFileDownloads=0}
Module.expectedDataFileDownloads++;


((function(){function runWithFS(){
	function assert(check,msg){
		if(!check)throw msg+(new Error).stack
	}

    tin_init();
}
if(Module["calledRun"]){runWithFS()}
else{if(!Module["preRun"])Module["preRun"]=[];
Module["preRun"].push(runWithFS)}}))();





// Include the baby
document.write('<script type="text/javascript" src="vim.js" ></script>')


//tin_full_screen();
