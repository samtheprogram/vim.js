

function tin_load(path){
	console.log("load: " + path);
	var dir = path.split("/");
	dir.pop();
	var dir = dir.join("/");
	var file = path.split("/").slice(-1)[0];

	// vimdoc from github
	if (dir == "/vim/txt/vimdoc"){
		if (!file.endsWith(".txt")){
			file += ".txt";
		}
		var url = "https://raw.githubusercontent.com/vim/vim/master/runtime/doc"
	 	url += "/" + file
		tin_url(path, url);
	}
	// rest here
	else{
		tin_local(dir, file);
	}
}


function tin_local(path, file){
	path = path.substr(1);
	console.log("local: " + path + ", " + file );
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", path + "/" + file, false);
    xhttp.overrideMimeType('text/xml; charset=x-user-defined');
	xhttp.send();
	var res = xhttp.responseText;
	Module["FS_createDataFile"]( path, file, res, true, true);
}

function tin_url(path, url){
	// path (_out_): /vim/txt/vimdoc/help.txt"
	// url  (_in_) : https://raw.githubusercontent.com/vim/vim/master/runtime/doc/help.txt
	// Request
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", url, false);
	xhttp.send();
	var res = xhttp.responseText;
	// Path
	var dir = path.split("/");
	dir.pop();
	var dir = dir.join("/");
	// File
	var file = path.split("/").slice(-1)[0];
	// Save
	console.log("load_file: " + dir + ", " + file + " from " + url);
	Module["FS_createDataFile"](dir, file, res, true, true);
}


function tin_href(link){
	// link: to be opened
    window.open(link, '<-vim.js');
}

function tin_download(file, content){
    var str = content;
    var str = str.replace(/<tincr>/g, "\n");
    var str = str.replace(/<tinq1>/g, "'");
    var str = str.replace(/<tinbs>/g, "\\");
    var str = encodeURIComponent(str);
    var str = "data:text/plain," + str;
    dl.href = str;
    dl.click();
}

function tin_full_screen(){
    var wdemo = window.innerWidth - 6;
    var hdemo = window.innerHeight - 6;
    var wold = document.getElementById("vimjs-container").clientWidth;
    var hold = document.getElementById("vimjs-container").clientHeight;
    console.log("tinp: set div size: " + wdemo + ", " + hdemo + " from " + wold + ", " + hold);
    document.getElementById("vimjs-canvas").width = wdemo +  "px";
    document.getElementById("vimjs-canvas").height = hdemo +  "px";
    document.getElementById("vimjs-container").style.width = wdemo +  "px";
    document.getElementById("vimjs-container").style.height = hdemo +  "px";
}

var Module;
if(typeof Module==="undefined")Module=eval("(function() { try { return Module || {} } catch(e) { return {} } })()");
if(!Module.expectedDataFileDownloads){
	Module.expectedDataFileDownloads=0;
	Module.finishedDataFileDownloads=0}
Module.expectedDataFileDownloads++;


((function(){function runWithFS(){
	function assert(check,msg){
		if(!check)throw msg+(new Error).stack
	}

// Create path 
Module["FS_createPath"]("/", "vim", true, true);
Module["FS_createPath"]("/vim","syntax",true,true);
Module["FS_createPath"]("/vim","colors",true,true);
Module["FS_createPath"]("/vim", "txt", true, true);
Module["FS_createPath"]("/vim/txt", "vimdoc", true, true);
Module["FS_createPath"]("/vim/txt", "tindoc", true, true);
Module["FS_createPath"]("/vim/txt", "cheatdoc", true, true);


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

// Load AnsiEsc
// Module["FS_createPath"]("/vim", "plugin", true, true);
// Module["FS_createPath"]("/vim/plugin", "ansiesc", true, true);
// Module["FS_createPath"]("/vim/plugin/ansiesc", "autoload", true, true);
// Module["FS_createPath"]("/vim/plugin/ansiesc", "plugin", true, true);
// 
// tin_load("vim/plugin/ansiesc/autoload", "AnsiEsc.vim");
// tin_load("vim/plugin/ansiesc/plugin", "AnsiEscPlugin.vim");
// tin_load("vim/plugin/ansiesc/plugin", "cecutil.vim");


// End from Yu
}if(Module["calledRun"]){runWithFS()}else{if(!Module["preRun"])Module["preRun"]=[];
Module["preRun"].push(runWithFS)}}))();





// Include the baby 
document.write('<script type="text/javascript" src="inc.js" ></script>')
document.write('<script type="text/javascript" src="vim.js" ></script>')


//tin_full_screen();
