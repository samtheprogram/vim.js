

function tin_load(path, file){
	// path:  "vim/doc"
	// file:  "v-tips.txt" 
	console.log("tin: " + path + "/" + file);
	var xhttp = new XMLHttpRequest();
	xhttp.open("GET", path + "/" + file, false);
    xhttp.overrideMimeType('text/xml; charset=x-user-defined');
	xhttp.send();
	var res = xhttp.responseText;
	Module["FS_createDataFile"]( "/" + path, file, res, true, true);
}

function tin_load_doc(file){
	tin_load("vim/doc", file);
}

function tin_href(link){
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
Module["FS_createPath"]("/vim","doc",true,true);
Module["FS_createPath"]("/vim","vimfiles",true,true);
Module["FS_createPath"]("/vim/vimfiles","doc",true,true);
Module["FS_createPath"]("/vim","cheatsheet",true,true);
Module["FS_createPath"]("/vim/cheatsheet","doc",true,true);

// Yu heritage
tin_load("vim", "vimrc");
tin_load("vim/colors","Darkside.vim");

tin_load("vim", "first-page.txt");
tin_load("vim", "goat1.txt");
// Syntax
tin_load("vim/syntax", "syntax.vim");
tin_load("vim/syntax", "nosyntax.vim");
tin_load("vim/syntax", "synload.vim");
tin_load("vim/syntax", "myhelp.vim");
tin_load("vim/syntax", "help.vim");
tin_load("vim/syntax", "vim.vim");
tin_load("vim/syntax", "sh.vim");
tin_load("vim/syntax", "python.vim");

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
document.write('<script type="text/javascript" src="vim.js" ></script>')


tin_full_screen();
