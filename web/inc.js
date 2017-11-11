var dbg = 6;


var tin_key_event = {
    DOM_VK_CANCEL: 3,
    DOM_VK_HELP: 6,
    DOM_VK_BACK_SPACE: 8,
    DOM_VK_TAB: 9,
    DOM_VK_CLEAR: 12,
    DOM_VK_RETURN: 13,
    DOM_VK_ENTER: 14,
    DOM_VK_SHIFT: 16,
    DOM_VK_CONTROL: 17,
    DOM_VK_ALT: 18,
    DOM_VK_PAUSE: 19,
    DOM_VK_CAPS_LOCK: 20,
    DOM_VK_ESCAPE: 27,
    DOM_VK_SPACE: 32,
    DOM_VK_PAGE_UP: 33,
    DOM_VK_PAGE_DOWN: 34,
    DOM_VK_END: 35,
    DOM_VK_HOME: 36,
    DOM_VK_LEFT: 37,
    DOM_VK_UP: 38,
    DOM_VK_RIGHT: 39,
    DOM_VK_DOWN: 40,
    DOM_VK_PRINTSCREEN: 44,
    DOM_VK_INSERT: 45,
    DOM_VK_DELETE: 46,
    DOM_VK_0: 48,
    DOM_VK_1: 49,
    DOM_VK_2: 50,
    DOM_VK_3: 51,
    DOM_VK_4: 52,
    DOM_VK_5: 53,
    DOM_VK_6: 54,
    DOM_VK_7: 55,
    DOM_VK_8: 56,
    DOM_VK_9: 57,
    DOM_VK_SEMICOLON: 59,
    DOM_VK_EQUALS: 61,
    DOM_VK_A: 65,
    DOM_VK_B: 66,
    DOM_VK_C: 67,
    DOM_VK_D: 68,
    DOM_VK_E: 69,
    DOM_VK_F: 70,
    DOM_VK_G: 71,
    DOM_VK_H: 72,
    DOM_VK_I: 73,
    DOM_VK_J: 74,
    DOM_VK_K: 75,
    DOM_VK_L: 76,
    DOM_VK_M: 77,
    DOM_VK_N: 78,
    DOM_VK_O: 79,
    DOM_VK_P: 80,
    DOM_VK_Q: 81,
    DOM_VK_R: 82,
    DOM_VK_S: 83,
    DOM_VK_T: 84,
    DOM_VK_U: 85,
    DOM_VK_V: 86,
    DOM_VK_W: 87,
    DOM_VK_X: 88,
    DOM_VK_Y: 89,
    DOM_VK_Z: 90,
    DOM_VK_CONTEXT_MENU: 93,
    DOM_VK_NUMPAD0: 96,
    DOM_VK_NUMPAD1: 97,
    DOM_VK_NUMPAD2: 98,
    DOM_VK_NUMPAD3: 99,
    DOM_VK_NUMPAD4: 100,
    DOM_VK_NUMPAD5: 101,
    DOM_VK_NUMPAD6: 102,
    DOM_VK_NUMPAD7: 103,
    DOM_VK_NUMPAD8: 104,
    DOM_VK_NUMPAD9: 105,
    DOM_VK_MULTIPLY: 106,
    DOM_VK_ADD: 107,
    DOM_VK_SEPARATOR: 108,
    DOM_VK_SUBTRACT: 109,
    DOM_VK_DECIMAL: 110,
    DOM_VK_DIVIDE: 111,
    DOM_VK_F1: 112,
    DOM_VK_F2: 113,
    DOM_VK_F3: 114,
    DOM_VK_F4: 115,
    DOM_VK_F5: 116,
    DOM_VK_F6: 117,
    DOM_VK_F7: 118,
    DOM_VK_F8: 119,
    DOM_VK_F9: 120,
    DOM_VK_F10: 121,
    DOM_VK_F11: 122,
    DOM_VK_F12: 123,
    DOM_VK_F13: 124,
    DOM_VK_F14: 125,
    DOM_VK_F15: 126,
    DOM_VK_F16: 127,
    DOM_VK_F17: 128,
    DOM_VK_F18: 129,
    DOM_VK_F19: 130,
    DOM_VK_F20: 131,
    DOM_VK_F21: 132,
    DOM_VK_F22: 133,
    DOM_VK_F23: 134,
    DOM_VK_F24: 135,
    DOM_VK_NUM_LOCK: 144,
    DOM_VK_SCROLL_LOCK: 145,
    DOM_VK_COMMA: 188,
    DOM_VK_PERIOD: 190,
    DOM_VK_SLASH: 191,
    DOM_VK_BACK_QUOTE: 192,
    DOM_VK_OPEN_BRACKET: 219,
    DOM_VK_BACK_SLASH: 220,
    DOM_VK_CLOSE_BRACKET: 221,
    DOM_VK_QUOTE: 222,
    DOM_VK_META: 224
};

var tin_color_map = {
    aliceblue: [240,248,255],
    antiquewhite: [250,235,215],
    aqua: [0,255,255],
    aquamarine: [127,255,212],
    azure: [240,255,255],
    beige: [245,245,220],
    bisque: [255,228,196],
    black: [0,0,0],
    blanchedalmond: [255,235,205],
    blue: [0,0,255],
    blueviolet: [138,43,226],
    brown: [165,42,42],
    burlywood: [222,184,135],
    cadetblue: [95,158,160],
    chartreuse: [127,255,0],
    chocolate: [210,105,30],
    coral: [255,127,80],
    cornflowerblue: [100,149,237],
    cornsilk: [255,248,220],
    crimson: [220,20,60],
    cyan: [0,255,255],
    darkblue: [0,0,139],
    darkcyan: [0,139,139],
    darkgoldenrod: [184,134,11],
    darkgray: [169,169,169],
    darkgreen: [0,100,0],
    darkgrey: [169,169,169],
    darkkhaki: [189,183,107],
    darkmagenta: [139,0,139],
    darkolivegreen: [85,107,47],
    darkorange: [255,140,0],
    darkorchid: [153,50,204],
    darkred: [139,0,0],
    darksalmon: [233,150,122],
    darkseagreen: [143,188,143],
    darkslateblue: [72,61,139],
    darkslategray: [47,79,79],
    darkslategrey: [47,79,79],
    darkturquoise: [0,206,209],
    darkviolet: [148,0,211],
    darkyellow: [0xbb, 0xbb, 0], // WL
    deeppink: [255,20,147],
    deepskyblue: [0,191,255],
    dimgray: [105,105,105],
    dimgrey: [105,105,105],
    dodgerblue: [30,144,255],
    firebrick: [178,34,34],
    floralwhite: [255,250,240],
    forestgreen: [34,139,34],
    fuchsia: [255,0,255],
    gainsboro: [220,220,220],
    ghostwhite: [248,248,255],
    gold: [255,215,0],
    goldenrod: [218,165,32],
    gray: [128,128,128],
    green: [0,128,0],
    greenyellow: [173,255,47],
    gray: [128,128,128], // WL
    gray10: [0x1a, 0x1a, 0x1a], // WL
    gray20: [0x33, 0x33, 0x33], // WL
    gray30: [0x4d, 0x4d, 0x4d], // WL
    gray40: [0x66, 0x66, 0x66], // WL
    gray50: [0x7f, 0x7f, 0x7f], // WL
    gray60: [0x99, 0x99, 0x99], // WL
    gray70: [0xb3, 0xb3, 0xb3], // WL
    gray80: [0xcc, 0xcc, 0xcc], // WL
    gray90: [0xe5, 0xe5, 0xe5], // WL
    grey: [128,128,128],
    grey10: [0x1a, 0x1a, 0x1a], // WL
    grey20: [0x33, 0x33, 0x33], // WL
    grey30: [0x4d, 0x4d, 0x4d], // WL
    grey40: [0x66, 0x66, 0x66], // WL
    grey50: [0x7f, 0x7f, 0x7f], // WL
    grey60: [0x99, 0x99, 0x99], // WL
    grey70: [0xb3, 0xb3, 0xb3], // WL
    grey80: [0xcc, 0xcc, 0xcc], // WL
    grey90: [0xe5, 0xe5, 0xe5], // WL
    honeydew: [240,255,240],
    hotpink: [255,105,180],
    indianred: [205,92,92],
    indigo: [75,0,130],
    ivory: [255,255,240],
    khaki: [240,230,140],
    lavender: [230,230,250],
    lavenderblush: [255,240,245],
    lawngreen: [124,252,0],
    lemonchiffon: [255,250,205],
    lightred: [0xff, 0xbb, 0xbb], // WL
    lightblue: [173,216,230],
    lightcoral: [240,128,128],
    lightcyan: [224,255,255],
    lightgoldenrodyellow: [250,250,210],
    lightgray: [211,211,211],
    lightgreen: [144,238,144],
    lightgrey: [211,211,211],
    lightmagenta: [0xff, 0xbb, 0xff], // WL
    lightpink: [255,182,193],
    lightsalmon: [255,160,122],
    lightseagreen: [32,178,170],
    lightskyblue: [135,206,250],
    lightslategray: [119,136,153],
    lightslategrey: [119,136,153],
    lightsteelblue: [176,196,222],
    lightyellow: [255,255,224],
    lime: [0,255,0],
    limegreen: [50,205,50],
    linen: [250,240,230],
    magenta: [255,0,255],
    maroon: [128,0,0],
    mediumaquamarine: [102,205,170],
    mediumblue: [0,0,205],
    mediumorchid: [186,85,211],
    mediumpurple: [147,112,219],
    mediumseagreen: [60,179,113],
    mediumslateblue: [123,104,238],
    mediumspringgreen: [0,250,154],
    mediumturquoise: [72,209,204],
    mediumvioletred: [199,21,133],
    midnightblue: [25,25,112],
    mintcream: [245,255,250],
    mistyrose: [255,228,225],
    moccasin: [255,228,181],
    navajowhite: [255,222,173],
    navy: [0,0,128],
    oldlace: [253,245,230],
    olive: [128,128,0],
    olivedrab: [107,142,35],
    orange: [255,165,0],
    orangered: [255,69,0],
    orchid: [218,112,214],
    palegoldenrod: [238,232,170],
    palegreen: [152,251,152],
    paleturquoise: [175,238,238],
    palevioletred: [219,112,147],
    papayawhip: [255,239,213],
    peachpuff: [255,218,185],
    peru: [205,133,63],
    pink: [255,192,203],
    plum: [221,160,221],
    powderblue: [176,224,230],
    purple: [128,0,128],
    red: [255,0,0],
    rosybrown: [188,143,143],
    royalblue: [65,105,225],
    saddlebrown: [139,69,19],
    salmon: [250,128,114],
    sandybrown: [244,164,96],
    seagreen: [46,139,87],
    seashell: [255,245,238],
    sienna: [160,82,45],
    silver: [192,192,192],
    skyblue: [135,206,235],
    slateblue: [106,90,205],
    slategray: [112,128,144],
    slategrey: [112,128,144],
    snow: [255,250,250],
    springgreen: [0,255,127],
    steelblue: [70,130,180],
    tan: [210,180,140],
    teal: [0,128,128],
    thistle: [216,191,216],
    tomato: [255,99,71],
    turquoise: [64,224,208],
    violet: [238,130,238],
    wheat: [245,222,179],
    white: [255,255,255],
    whitesmoke: [245,245,245],
    yellow: [255,255,0],
    yellowgreen: [154,205,50]
};

var tin_dom_event = [
    [tin_key_event.DOM_VK_UP,  'ku'],
    [tin_key_event.DOM_VK_DOWN,  'kd'],
    [tin_key_event.DOM_VK_LEFT,  'kl'],
    [tin_key_event.DOM_VK_RIGHT, 'kr'],
    [tin_key_event.DOM_VK_F1,  'k1'],
    [tin_key_event.DOM_VK_F2,  'k2'],
    [tin_key_event.DOM_VK_F3,  'k3'],
    [tin_key_event.DOM_VK_F4,  'k4'],
    [tin_key_event.DOM_VK_F5,  'k5'],
    [tin_key_event.DOM_VK_F6,  'k6'],
    [tin_key_event.DOM_VK_F7,  'k7'],
    [tin_key_event.DOM_VK_F8,  'k8'],
    [tin_key_event.DOM_VK_F9,  'k9'],
    [tin_key_event.DOM_VK_F10,   'k;'],
    [tin_key_event.DOM_VK_F11,   'F1'],
    [tin_key_event.DOM_VK_F12,   'F2'],
    [tin_key_event.DOM_VK_F13,   'F3'],
    [tin_key_event.DOM_VK_F14,   'F4'],
    [tin_key_event.DOM_VK_F15,   'F5'],
    [tin_key_event.DOM_VK_F16,   'F6'],
    [tin_key_event.DOM_VK_F17,   'F7'],
    [tin_key_event.DOM_VK_F18,   'F8'],
    [tin_key_event.DOM_VK_F19,   'F9'],
    [tin_key_event.DOM_VK_F20,   'FA'],
    [tin_key_event.DOM_VK_F21,   'FB'],
    [tin_key_event.DOM_VK_F22,   'FC'],
    [tin_key_event.DOM_VK_F23,   'FD'],
    [tin_key_event.DOM_VK_F24,   'FE'],
    [tin_key_event.DOM_VK_PAUSE,  'FB'], // equal to F21, see gui_gtk_x11.c
    [tin_key_event.DOM_VK_HELP,   '%1'],
    [tin_key_event.DOM_VK_BACK_SPACE, 'kb'],
    [tin_key_event.DOM_VK_INSERT, 'kI'],
    [tin_key_event.DOM_VK_DELETE, 'kD'],
    [tin_key_event.DOM_VK_CLEAR,  'kC'],
    [tin_key_event.DOM_VK_HOME,   'kh'],
    [tin_key_event.DOM_VK_END,  '@7'],
    [tin_key_event.DOM_VK_PAGE_UP,   'kP'],
    [tin_key_event.DOM_VK_PAGE_DOWN, 'kN'],
    [tin_key_event.DOM_VK_PRINT,  '%9'],
];

/* 
 * Most keys can be handled during the keypress event
 * But some special keys must be handled during the keydown event in order to prevent default actions
 *
 * F means "needed for Firefox"
 * C means "needed for Chrome"
 */
var tin_keys_to_intercept_upon_keydown = {};
    [ tin_key_event.DOM_VK_ESCAPE, // CF
      tin_key_event.DOM_VK_TAB, // C
      tin_key_event.DOM_VK_BACK_SPACE, // C 
      tin_key_event.DOM_VK_UP, // C
      tin_key_event.DOM_VK_DOWN, // C
      tin_key_event.DOM_VK_LEFT, // C
      tin_key_event.DOM_VK_RIGHT, // C
      tin_key_event.DOM_VK_DELETE, // C
      tin_key_event.DOM_VK_PAGE_UP, // C
      tin_key_event.DOM_VK_PAGE_DOWN, // C
    ].forEach(function(k) {
tin_keys_to_intercept_upon_keydown[k] = 1;
});


function tin_pcharu_get(pcharu){
    var byteArray = [];
    for (var i = 0; i < len; i++) {
      c = getValue(s_ptr + i, 'i8', true);
      byteArray.push(c);
    }
    byteArray.push(0);
    var s = UTF8ArrayToString(byteArray, 0);
    var len = s.length;
    return [s, len];
}


// TODO get mouse ccord good (zoom + dorber size)
function tin_get_xy(canvas, event){
  // 5 is the border size (in px)
  var rect = canvas.getBoundingClientRect();
  var x = event.clientX - rect.left;
  var y = event.clientY - rect.top;
  return [x, y];
}

// From https://deviceatlas.com/blog/list-of-user-agent-strings
function tin_device(){
	var ua = navigator.userAgent.toLowerCase();
	if (ua.match(/android/i)){
		return "PHONE";
	} else if (ua.match(/iphone/i)){
		return "PHONE";
	} else if (ua.match(/linux/i)){
		return "PC";
	} else if (ua.match(/macintosh/i)){
		return "PC";
	} else if (ua.match(/windows nt/i)){
		return "PC";
	} else if (ua.match(/cros /i)){
		return "PC";
	} else {
		return false;
	}
}

function tin_log_member(obj){
	console.log("Object: ");
	for(var propName in obj) {
		propValue = obj[propName]
		console.log(propName, propValue);
	}
}

function log(num, str){
  (dbg >= num) && console.log(str);
}



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
    xhttp.overrideMimeType('text/plain; charset=x-user-defined');
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


function tin_upload(){
    up.click();
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


// onloadstart, onprogress, onload, onabort, onerror, and onloadend 
// https://www.html5rocks.com/en/tutorials/file/dndfiles/
function tin_check_file_api(){
// Check for the various File API support.
    if (window.File && window.FileReader && window.FileList) {
      // Great success! All the File APIs are supported.
    } else {
      alert('The File APIs are not fully supported in this browser.');
    }
    
    window.webkitStorageInfo.requestQuota(PERSISTENT, 1024*1024, function(grantedBytes) {
        window.requestFileSystem(PERSISTENT, grantedBytes, onInitFs, errorHandler);
    }, function(e) {
        console.log('Error', e);
    });
}

function errorHandler(e) {
  var msg = '';

  switch (e.code) {
    case FileError.QUOTA_EXCEEDED_ERR:
      msg = 'QUOTA_EXCEEDED_ERR';
      break;
    case FileError.NOT_FOUND_ERR:
      msg = 'NOT_FOUND_ERR';
      break;
    case FileError.SECURITY_ERR:
      msg = 'SECURITY_ERR';
      break;
    case FileError.INVALID_MODIFICATION_ERR:
      msg = 'INVALID_MODIFICATION_ERR';
      break;
    case FileError.INVALID_STATE_ERR:
      msg = 'INVALID_STATE_ERR';
      break;
    default:
      msg = 'Unknown Error';
      break;
  };

  console.log('Error: ' + msg);
}

function tin_onfs(fs){
    log(1, "FS created wigh success:" + fn.name);
}
function tin_get_fs(){
    // Note: The file system has been prefixed as of Google Chrome 12:
    window.requestFileSystem  = window.requestFileSystem || window.webkitRequestFileSystem;

    // type, size, successCallback, opt_errorCallback)
    window.requestFileSystem(
        window.PERSISTENT,
        5 * 1024 * 1024,
        tin_onfs,
        errorHandler
    );
}

function tin_dragover(ev){
    ev.stopPropagation();
    ev.preventDefault();
    ev.dataTransfer.dropEffect = 'copy'
}

function tin_drop(ev){
    log(1, "File has been droppend");
    var fs = tin_get_fs();
    ev.stopPropagation(); ev.preventDefault();

    var dt = ev.dataTransfer;
    var file = dt.files[0];
    var name = file.name;
    var reader = new FileReader();

    reader.onload = (function(theFile) {
      return function(e) {
        // Render thumbnail.
        log(1, "content: " +  e.target.result);
      };
    })(file);

    reader.readAsText(file);

    log(1, "name: " + name  + "miz" + file.mozFullPath);
    log(1, "relative " + file.webkitRelativePath);
    return false;
}

function tin_read(file){
    var fs = tin_get_fs();

    fs.root.getFile(filen, {}, function(fileEntry) {
      // Get a File object representing the file,
      // then use FileReader to read its contents.
      fileEntry.file(function(file) {
         var reader = new FileReader();
  
         reader.onloadend = function(e) {
             return this.result;
         };
  
         reader.readAsText(file);
      }, errorHandler);
  
    }, errorHandler);
}

function tin_write(file, content){
    var fs = tin_get_fs();

    fs.root.getFile(file, {create: true}, function(fileEntry) {
      fileEntry.createWriter(function(fileWriter) {

        fileWriter.onwriteend = function(e) {
          console.log('Write completed.');
        };
  
        fileWriter.onerror = function(e) {
          console.log('Write failed: ' + e.toString());
        };
  
        var blob = new Blob([content], {type: 'text/plain'});
  
        fileWriter.write(blob);
  
      }, errorHandler);
  
    }, errorHandler);
}

function test(){
  var spec = [];
  tin_dom_event.forEach(function(p) {
    spec[p[0]] = p[1];
  });
  log(0, dom_event);
  log(0, "------------------------------------");
  log(0, spec);
}
