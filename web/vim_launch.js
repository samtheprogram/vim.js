


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
Module["FS_createPath"]("/vim","plugin",true,true);
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


// End from Yu
}if(Module["calledRun"]){runWithFS()}else{if(!Module["preRun"])Module["preRun"]=[];
Module["preRun"].push(runWithFS)}}))();





// Include the baby 
document.write('<script type="text/javascript" src="inc.js" ></script>')
document.write('<script type="text/javascript" src="vim.js" ></script>')


//tin_full_screen();
