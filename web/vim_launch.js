document.write('<script type="text/javascript" src="inc.js" ></script>')

// Prepare ground
function tin_init(){
	// Set size for android soft keyboard
    if (tin_device() == "PHONE"){
		log(1, "I am on phone");
		var div = document.getElementById('vimjs-container');
		div.style.bottom = "40%";
		div.style.height = "56%";
	}
	else{
		log(1, "I am on PC");
	}

    // Create path
    Module["FS_createPath"]("/", "local", true, true);
    Module["FS_createPath"]("/", "vim", true, true);
    Module["FS_createPath"]("/vim", "plugin", true, true);
    Module["FS_createPath"]("/vim", "syntax", true, true);
    Module["FS_createPath"]("/vim", "colors", true, true);
    Module["FS_createPath"]("/vim", "txt", true, true);
    Module["FS_createPath"]("/vim", "script", true, true);
    Module["FS_createPath"]("/vim/txt", "vimdoc", true, true);
    Module["FS_createPath"]("/vim/txt", "tindoc", true, true);
    Module["FS_createPath"]("/vim/txt", "cheatdoc", true, true);
    Module["FS_createPath"]("/vim/txt", "mess", true, true);

	// Plugin (TODO remove)
    Module["FS_createPath"]("/vim/plugin", "airline", true, true);
    Module["FS_createPath"]("/vim/plugin/airline", "autoload", true, true);
    Module["FS_createPath"]("/vim/plugin/airline/autoload", "airline", true, true);
    Module["FS_createPath"]("/vim/plugin/airline/autoload/airline", "extensions", true, true);
    Module["FS_createPath"]("/vim/plugin/airline/autoload/airline", "themes", true, true);
    Module["FS_createPath"]("/vim/plugin", "ctrlp", true, true);
    Module["FS_createPath"]("/vim/plugin/ctrlp", "autoload", true, true);
    Module["FS_createPath"]("/vim/plugin/ctrlp/autoload", "ctrlp", true, true);
    Module["FS_createPath"]("/vim/plugin", "undotree", true, true);
    Module["FS_createPath"]("/vim/plugin/undotree", "syntax", true, true);
    Module["FS_createPath"]("/vim/plugin", "easymotion", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion", "autoload", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion", "autoload", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload", "EasyMotion", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/EasyMotion", "migemo", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload", "vital", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital", "_easymotion", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion", "Over", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion", "Data", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion", "Palette", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion", "Vim", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion", "Vim", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion/Over", "Commandline", true, true);
    Module["FS_createPath"]("/vim/plugin/easymotion/autoload/vital/_easymotion/Over/Commandline", "Modules", true, true);


    // Load first page
    tin_load("/vim/first-page.txt");

    // Vimrc
    tin_load("/vim/vimrc");
    tin_load("/vim/script/color.vim");
    tin_load("/vim/script/net.vim");
    tin_load("/vim/script/plugin.vim");

    // Syntax
    tin_load("/vim/colors/Darkside.vim");
    tin_load("/vim/syntax/syntax.vim");
    tin_load("/vim/syntax/nosyntax.vim");
    tin_load("/vim/syntax/synload.vim");
    tin_load("/vim/syntax/myhelp.vim");
    tin_load("/vim/syntax/help.vim");
}


// Define Module
var Module = {
  noInitialRun: false,
  noExitRuntime: true,
  arguments: ['vim/first-page.txt'],
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
  'vimjs-exit': function(status) {
    console.log('vimjs exited:',status);
  },
};


// Load dat
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
