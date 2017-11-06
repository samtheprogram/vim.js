/*  vim: set sw=2 ts=2 et ft=javascript foldmethod=marker foldmarker=VIMJS_FOLD_START,VIMJS_FOLD_END : */
/*
 * vim_lib.js: connect DOM and user inputs to Vim.js
 *
 * Copyright (c) 2013,2014 Lu Wang <coolwanglu@gmail.com>
 */

/*
 * $vimjs holds the common states and functions
 * vimjs_* functions are exposed to C
 */
var LibraryVIM = {
  $vimjs__deps: ['mktemp'],
  $vimjs: {
    is_firefox: false,
    is_chrome: false,

    // HTML elements
    container_node: null,
    canvas_node: null,
    beep_node: null, // for beeping
    file_node: null, // file selector
    font_test_node: null,
    trigger_dialog_node: null, // to trigger file selector

    canvas_ctx: null,

    // dimensions
    devicePixelRatio: 0,
    char_width: 1,
    char_height: 1,
    window_width: 0,
    window_height: 0,

    // styles
    font: '20px monospace',
    fg_color: '#fff',
    bg_color: '#000',
    sp_color: '#f00',

    // functions 
    gui_web_handle_key: null,
    input_available: null,

    special_keys: [],
    special_keys_namemap: {},
    color_map: {},
    file_callback: null,
    dropbox_callback: null,
    trigger_callback: null,

    // Var
    KeyEvent: null,
    // workaround for ^W on non-firefox
    ctrl_pressed: false,



    dropbox: null,

    // functions that are not exposed to C
    handle_key: function(charCode, keyCode, e) {//VIMJS_FOLD_START
      // macros defined in keymap.h
      var modifiers = 0;
      // shift already affects charCode
      if(charCode && e.shiftKey) modifiers |= 0x02;
      if(e.ctrlKey) modifiers |= 0x04;
      if(e.altKey) modifiers |= 0x08;
      if(e.metaKey) modifiers |= 0x10;

      var handled = false;
      if(charCode == 0) {
        var special = vimjs.special_keys[keyCode];
        if(special !== undefined) {
          vimjs.gui_web_handle_key(charCode || keyCode, modifiers, special.charCodeAt(0), special.charCodeAt(1));
          handled = true;
        } 
      }

      if(!handled){
        if (keyCode == vimjs.KeyEvent.DOM_VK_ESCAPE ||
            keyCode == vimjs.KeyEvent.DOM_VK_TAB){
          vimjs.gui_web_handle_key(charCode || keyCode, modifiers, 0, 0);
        }
        else {
          var MAX_UTF8_BYTES = 6;
          var chars = new Uint8Array(MAX_UTF8_BYTES + 1); // null-terminated
          var charLen = stringToUTF8Array(String.fromCharCode(charCode), chars, 0, MAX_UTF8_BYTES);
          if (charLen == 1) {
            vimjs.gui_web_handle_key(chars[0], modifiers, 0, 0);
          } else {
            // no modifers for UTF-8, should be handled in chars already
            for (var i = 0; i < charLen; i++) {
              vimjs.gui_web_handle_key(chars[i], 0, 0, 0);
            }
          }
        }
      }

    },//VIMJS_FOLD_END

    get_color_string: function(color) {
      var bgr = [];
      for(var i = 0; i < 3; ++i) {
        bgr.push(color & 0xff);
        color >>= 8;
      }
      return 'rgb('+bgr[2]+','+bgr[1]+','+bgr[0]+')';
    },

    // dirty works, called before the program starts
    pre_run: function () {//VIMJS_FOLD_START
      // setup directories & environment
      ENV['USER'] = 'tinmarino';
      ENV['HOME'] = '/'; 
      ENV['PWD'] = '/';
      ENV['_'] = '/vim';
      ENV['VIMRUNTIME'] = '/vim';
    },//VIMJS_FOLD_END

    // load external resources

    // On some browsers file selector cannot
    // be trigger unless inside a user event
    user_trigger: function (cb) {
      if(vimjs.is_chrome) {
        vimjs.trigger_callback = function() {
          vimjs.trigger_dialog_node.parentNode.removeChild(vimjs.trigger_dialog_node);
          setTimeout(cb, 1);
        };

        // vimjs.container_node.appendChild(vimjs.trigger_dialog_node);

      } else {
        cb();
      }
    },
    
    // load file from different locations
    load_nothing: function (cb, buf) {
      {{{ makeSetValue('buf', 0, 0, 'i8') }}};
      setTimeout(cb, 1);
    },

    // save data to a temp file and return it to Vim
    load_data: function (cb, buf, data_array) {
      writeArrayToMemory(intArrayFromString('/tmp/vimjs-XXXXXX'), buf);
      _mktemp(buf);
      FS.writeFile(Pointer_stringify(buf), data_array, { encoding: 'binary' });
      setTimeout(cb, 1);
    },

    // load local file
    load_local_file: function (cb, buf) {
      // read from local
      vimjs.file_callback = function (files) {
        vimjs.file_callback = null;
        if(files.length == 0) {
          vimjs.load_nothing(cb, buf);
          return;
        }
        var reader = new FileReader();
        reader.onload = function(e) {
          vimjs.load_data(cb, buf, new Uint8Array(e.target.result));
        }
        reader.readAsArrayBuffer(files[0]);
      };
      vimjs.user_trigger(function() {
        vimjs.file_node.click();
      });
    },

    // load dropbox-js if necessary
    ensure_dropbox: function (cb) {
      if (typeof Dropbox === 'undefined') {
        // load js
        var ele = document.createElement('script');
        ele.id = 'dropboxjs';
        ele.setAttribute('data-app-key', 'ayzai5sqtyjydma');
        ele.onload = function() {
          cb();
        };
        ele.onerror = function() {
          ele.parentNode.removeChild(ele);
          cb();
        }
        ele.src = 'https://www.dropbox.com/static/api/1/dropins.js';
        document.body.appendChild(ele);
      } else {
        cb();
      }
    },

    load_dropbox_file: function (cb, buf) {
      if(typeof Dropbox === 'undefined') {
        vimjs.load_nothing(cb, buf);
        return;
      }
      vimjs.user_trigger(function() {
        Dropbox.choose({
          success: function(files) {
            var url = files[0].link;
            var xhr = new XMLHttpRequest();
            xhr.open('GET', url, true);
            xhr.responseType = 'arraybuffer';
            xhr.onload = function () {
              if (xhr.status == 200 || (xhr.status == 0 && xhr.response)) { // file URLs can return 0
                vimjs.load_data(cb, buf, new Uint8Array(xhr.response));
              } else {
                xhr.onerror();
              }
            };
            xhr.onerror = function() {
              vimjs.load_nothing(cb, buf);
            };
            xhr.send(null);
          },
          cancel: function() {
            vimjs.load_nothing(cb, buf);
          },
          linkType: 'direct',
          multiselect: false
        });
      });
    }, // VIMJS_FOLD_END

    invert_canvas: function(x, y, w, h) {
      var ctx = vimjs.canvas_ctx;
      var img = ctx.getImageData(x, y, w, h);
      var data = img.data;
      for(var i = 0, l = data.length; i < l;) {
        data[i] = 255 - data[i];
        ++i;
        data[i] = 255 - data[i];
        ++i;
        data[i] = 255 - data[i];
        i += 2;
      }
      ctx.putImageData(img, x, y);
    },


    __dummy__: null
  },

  vimjs_init__deps: ['vimjs_init_font'],
  vimjs_init: function () {
    vimjs.is_firefox = typeof InstallTrigger !== 'undefined';
    vimjs.is_chrome = !!window.chrome;
    
    vimjs.gui_web_handle_key = Module['cwrap']('gui_web_handle_key', null, 
      ['number', 'number', 'number', 'number']);
    vimjs.input_available = Module['cwrap']('input_available', 'number', []);
    vimjs.gui_send_mouse_event= Module['cwrap']('gui_send_mouse_event', null, 
      ['number', 'number', 'number', 'number', 'number']);
    vimjs.gui_mouse_moved= Module['cwrap']('gui_mouse_moved', null, 
      ['number', 'number']);

    vimjs.beep_node = document.getElementById('vimjs-beep');

    vimjs.file_node = document.getElementById('vimjs-file');
    vimjs.file_node.addEventListener('change', function(e) {
      if(vimjs.file_callback)
        vimjs.file_callback(e.target.files);
    });

    vimjs.font_test_node = document.getElementById('vimjs-font-test');

    document.getElementById('vimjs-trigger-button').addEventListener('click', function() {
      if(vimjs.trigger_callback)
        vimjs.trigger_callback();
    });
    var trigger_dialog_node =  vimjs.trigger_dialog_node = document.getElementById('vimjs-trigger-dialog');
    trigger_dialog_node.parentNode.removeChild(trigger_dialog_node);
    trigger_dialog_node.style.display = 'block';

    var canvas_node = vimjs.canvas_node = document.getElementById('vimjs-canvas');
    canvas_node.style.display = 'block';
    vimjs.canvas_ctx = canvas_node.getContext('2d');

    var container_node = vimjs.container_node = document.getElementById('vimjs-container');
    vimjs.devicePixelRatio = window.devicePixelRatio || 1;
    vimjs.window_width = container_node.clientWidth * vimjs.devicePixelRatio;
    vimjs.window_height = container_node.clientHeight * vimjs.devicePixelRatio;
    log(1, "init size: " + vimjs.window_width + ", " + vimjs.window_height);

    _vimjs_init_font('');

    // initialize special_keys
    vimjs.special_keys = [];
    vimjs.special_keys_namemap = {};
    /* for closure compiler */
    vimjs.KeyEvent = window.KeyEvent;
    /* for Chrome */
    /* http://stackoverflow.com/questions/1465374/javascript-event-keycode-constants/1465409#1465409 */
    if (typeof KeyEvent == "undefined") {
        vimjs.KeyEvent = tin_get_key_event();
    }
    var dom_event = tin_get_dom_event(vimjs.KeyEvent)
    dom_event.forEach(function(p) {
      vimjs.special_keys[p[0]] = p[1];
      vimjs.special_keys_namemap[p[1]] = p[0];
    });

    vimjs.color_map = tin_get_color_map();

    vimjs.lastMouseDownTarget = vimjs.canvas_node; // set focus on start
    var ignoreKeys = function() {
      return (vimjs.lastMouseDownTarget !== vimjs.canvas_node);
    }


    // Mouse Down
    var vimjs_mouse_down_event = function(event){
        var xy = tin_get_xy(vimjs.canvas_node, event);
        var x = xy[0];
        var y = xy[1];
        var button = event.button;
        var str = "Mouse Down: " + x + ", " + y + " pressed : " + button;
        log(2, str);
        vimjs.gui_send_mouse_event(button, x, y, false, 0);
    }
    document.addEventListener("mousedown", vimjs_mouse_down_event);
  
    // Mouse Wheel
    var vimjs_mouse_wheel_event = function(event){
        var xy = tin_get_xy(vimjs.canvas_node, event);
        var x = xy[0];
        var y = xy[1];
        var dir = event.deltaY;
        var button = 0;
        if (dir > 0){
          button = 0x200;
        }
        else{
          button = 0x100;
        }
        var str = "Mouse Wheel: " +  dir + ", " + button;
        log(2, str);
        vimjs.gui_send_mouse_event(button, x, y, false, 0);
    }
    document.addEventListener("wheel", vimjs_mouse_wheel_event, false);

    // Mouse Release
    var vimjs_mouse_release_event = function(event){
        var xy = tin_get_xy(vimjs.canvas_node, event);
        var x = xy[0];
        var y = xy[1];
        log(2, "Mouse Up: " + x + ", " + y);
        vimjs.gui_send_mouse_event(3, x, y, false, 0);
    }
    document.addEventListener("mouseup", vimjs_mouse_release_event);

    // Mouse move
    var vimjs_mouse_move_event = function(event){
        var xy = tin_get_xy(vimjs.canvas_node, event);
        var x = xy[0];
        var y = xy[1];
        log(9, "Mouse Move: " + y + ", " + y);
        // TODO if i did not click ? 
        // vimjs.gui_mouse_moved(x, y);
        vimjs.gui_send_mouse_event(0x43, x, y, false, 0);
    }
    document.addEventListener("mousemove", vimjs_mouse_move_event);


    document.addEventListener('mousedown', function(event) {
        if (vimjs.canvas_node.contains(event.target)) {
          vimjs.lastMouseDownTarget = vimjs.canvas_node;
        } else {
          vimjs.lastMouseDownTarget = event.target;
        }
      },
      false);

    document.addEventListener('keypress', function(e) {
      if (ignoreKeys()) return true;
      e.preventDefault();
      vimjs.handle_key(e.charCode, e.keyCode, e);
    });

    /* 
     * Most keys can be handled during the keypress event
     * But some special keys must be handled during the keydown event in order to prevent default actions
     *
     * F means "needed for Firefox"
     * C means "needed for Chrome"
     */
    var keys_to_intercept_upon_keydown = {};
    [ vimjs.KeyEvent.DOM_VK_ESCAPE, // CF
      vimjs.KeyEvent.DOM_VK_TAB, // C
      vimjs.KeyEvent.DOM_VK_BACK_SPACE, // C 
      vimjs.KeyEvent.DOM_VK_UP, // C
      vimjs.KeyEvent.DOM_VK_DOWN, // C
      vimjs.KeyEvent.DOM_VK_LEFT, // C
      vimjs.KeyEvent.DOM_VK_RIGHT, // C
      vimjs.KeyEvent.DOM_VK_DELETE, // C
      vimjs.KeyEvent.DOM_VK_PAGE_UP, // C
      vimjs.KeyEvent.DOM_VK_PAGE_DOWN, // C
    ].forEach(function(k) {
      keys_to_intercept_upon_keydown[k] = 1;
    });

    /* capture some special keys that won't trigger 'keypress' */
    document.addEventListener('keydown', function(e) {
      log(2, "Key Down: " + e.keyCode + "," + e);
      if (ignoreKeys()) return true;
      if(e.keyCode in keys_to_intercept_upon_keydown)  {
        log(2, "Key Down: is handled");
        e.preventDefault();
        vimjs.handle_key(0, e.keyCode, e);
      }
    });

    if(!vimjs.is_firefox) {
      // monitor ctrl for non-firefox
      // display dialog if ^W is pressed
      document.addEventListener('keydown', function(e) {
        if (ignoreKeys()) return true;
        if(e.keyCode === vimjs.KeyEvent.DOM_VK_CONTROL)
          vimjs.ctrl_pressed = true;
      });
      document.addEventListener('keyup', function(e) {
        if (ignoreKeys()) return true;
        if(e.keyCode === vimjs.KeyEvent.DOM_VK_CONTROL)
          vimjs.ctrl_pressed = false;
      });
    }
  }, // End of vimjs_init()

  vimjs_clip_set: function(s_ptr, size){
    // UTF8 pointer -> string
    var byteArray = [];
    for (var i = 0; i < size; i++) {
      c = getValue(s_ptr + i, 'i8', true);
      byteArray.push(c);
    }
    byteArray.push(0);
    var s = UTF8ArrayToString(byteArray, 0);
    var len = s.length;
    log(1, "Clipboard set: " + s);
    window.prompt("Copy me! (+OK)", s);
  },

  vimjs_clip_get: function(){
	  var str = window.prompt("Press Ctrl-V! (+OK)");
    log(1, "Clipboard get: " + str);
    var ptr = allocate(intArrayFromString(str), 'i8', ALLOC_NORMAL)
    return ptr;
    _free(ptr);
  },

  vimjs_log: function(num, str){
    console.log("C: " + Pointer_stringify(str));
  },
  
  vimjs_prepare_exit: function() {
    if(!!Module['VIMJS_ALLOW_EXIT']) {
      // This is likely to be set by async jobs
      // hack it to exit normally
      Module['noExitRuntime'] = false;
      return 1;
    } else {
      return 0;
    }
  },

  vimjs_beep: function() {
    var beep_node = vimjs.beep_node;
    /* sometimes this is called before vimjs.beep is initialized */
    if(beep_node) {
      if(vimjs.is_chrome) {
        // without this Chrome would only play it once
        beep_node.load(); 
      }
      beep_node.play();
    }
  },

  vimjs_flash__deps: ['emscripten_async_resume'],
  vimjs_flash: function(msec) {
    var canvas_node = vimjs.canvas_node;
    var w = canvas_node.width;
    var h = canvas_node.height;
    vimjs.invert_canvas(0, 0, w, h);
    setTimeout(function() {
      vimjs.invert_canvas(0, 0, w, h);
      asm['setAsync']();
      _emscripten_async_resume();
    }, msec);
  },

  vimjs_get_window_width: function() {
    return vimjs.window_width;
  },

  vimjs_get_window_height: function() {
    return vimjs.window_height;
  },

  vimjs_resize: function(width, height) {
    var container_node = vimjs.container_node;
    container_node.style.width = width / vimjs.devicePixelRatio + container_node.offsetWidth - container_node.clientWidth + 'px';
    container_node.style.height = height / vimjs.devicePixelRatio + container_node.offsetHeight - container_node.clientHeight + 'px';
    vimjs.canvas_node.width = width;
    vimjs.canvas_node.height = height;
  },



  vimjs_draw_string__deps: ['vimjs_clear_block'],
  vimjs_draw_string: function(row, col, s_ptr, len, flags) {
    var byteArray = [];
    for (var i = 0; i < len; i++) {
      c = getValue(s_ptr + i, 'i8', true);
      byteArray.push(c);
    }
    byteArray.push(0);
    var s = UTF8ArrayToString(byteArray, 0);
    var len = s.length;
    log(9, "Draw: " + len + ": " + s);

    // TODO: use macros for flag constants
  if(!(flags & 0x01)) {
    _vimjs_clear_block(row, col, row, col + len - 1);
  }

  var font = vimjs.font;
  if(flags & 0x02) font = 'bold ' + font;

  var ctx = vimjs.canvas_ctx;

  ctx.font = font;
  ctx.textBaseline = 'bottom';

  ctx.fillStyle = vimjs.fg_color;

  var x = col * vimjs.char_width;
  var y = (row + 1) * vimjs.char_height;
  var w = len * vimjs.char_width;
  ctx.fillText(s, x, y, w);

  if(flags & 0x04) { // underline
    ctx.strokeStyle = vimjs.fg_color;
    ctx.beginPath();
    ctx.moveTo(x, y - 0.5);
    ctx.lineTo(x + w, y - 0.5);
    ctx.stroke();
  }
  if(flags & 0x08) { // undercurl
    var offs = [1.5, 0.5, 0.5, 0.5, 1.5, 2.5, 2.5, 2.5];
    ctx.strokeStyle = vimjs.sp_color;
    ctx.beginPath();
    ctx.moveTo(x, y - offs[x%8]);

    for(var xx = x + 1, xx2 = x + w; xx < xx2; ++xx)
      ctx.lineTo(xx, y - offs[xx%8]);

    ctx.stroke();
  }
},

vimjs_clear_block: function(row1, col1, row2, col2) {
  var ctx = vimjs.canvas_ctx;
  ctx.fillStyle = vimjs.bg_color;
  var cw = vimjs.char_width;
  var ch = vimjs.char_height;
  ctx.fillRect(col1 * cw,
               row1 * ch,
               (col2-col1+1) * cw,
               (row2-row1+1) * ch);
},   

vimjs_clear_all: function() {
  var canvas_node = vimjs.canvas_node;
  var ctx = vimjs.canvas_ctx;
  ctx.fillStyle = vimjs.bg_color;
  ctx.fillRect(0, 0, canvas_node.width, canvas_node.height);
},

vimjs_delete_lines__deps: ['vimjs_clear_block'],
vimjs_delete_lines: function(num_lines, row1, row2, col1, col2) {
  var ctx = vimjs.canvas_ctx;
  var cw = vimjs.char_width;
  var ch = vimjs.char_height;
  var x = col1 * cw;
  var y = (row1 + num_lines) * ch;
  var w = (col2 - col1 + 1) * cw;
  var h = (row2 + 1) * ch - y;
  ctx.drawImage(vimjs.canvas_node, 
                x, y, w, h,
                x, row1 * ch, w, h);

  _vimjs_clear_block(row2 - num_lines + 1, col1, row2, col2);
},

vimjs_insert_lines__deps: ['vimjs_clear_block'],
vimjs_insert_lines: function(num_lines, row1, row2, col1, col2) {
  var ctx = vimjs.canvas_ctx;
  var cw = vimjs.char_width;
  var ch = vimjs.char_height;
  var x = col1 * cw;
  var w = (col2 - col1 + 1) * cw;
  var h = (row2 - row1 - num_lines + 1) * ch;
  ctx.drawImage(vimjs.canvas_node, 
                x, row1 * ch, w, h,
                x, (row1 + num_lines) * ch, w, h);

  _vimjs_clear_block(row1, col1, row1 + num_lines - 1, col2);
},

vimjs_draw_hollow_cursor: function(row, col) {
  var ctx = vimjs.canvas_ctx;
  ctx.strokeStyle = vimjs.fg_color;
  var cw = vimjs.char_width;
  var ch = vimjs.char_height;
  ctx.strokeRect(col * cw + 0.5, row * ch + 0.5, cw - 1, ch - 1);
},

vimjs_draw_part_cursor: function(row, col, width, height) {
  var ctx = vimjs.canvas_ctx;
  ctx.fillStyle = vimjs.fg_color;
  var cw = vimjs.char_width;
  var ch = vimjs.char_height;
  ctx.fillRect(col * cw, (row + 1) * ch - height, width, height);
},

vimjs_invert_rectangle: function(row, col, row_count, col_count) {
  var cw = vimjs.char_width;
  var ch = vimjs.char_height;
  vimjs.invert_canvas(col * cw, row * ch, col_count *cw, row_count * ch);
},

vimjs_init_font: function(font) {
  if(typeof font !== 'string')
    font = Pointer_stringify(font);
  if(!font)
    font = '16px monospace';

  var font_test_node = vimjs.font_test_node;
  font_test_node.style.font = font;
  font_test_node.innerHTML = 'm';

  /* clientWidth/Height won't work */
  vimjs.char_height = Math.max(1, font_test_node.clientHeight * vimjs.devicePixelRatio);
  vimjs.char_width = Math.max(1, font_test_node.clientWidth * vimjs.devicePixelRatio);
},

vimjs_set_font: function(font) {
  vimjs.font = Pointer_stringify(font);
  try {
    var l = vimjs.font.split(/([\d]+)(?=in|[cem]m|ex|p[ctx])/);
    l[1] = parseFloat(l[1]) * vimjs.devicePixelRatio;
    vimjs.font = l.join('');
  } catch (e) { }
},

vimjs_check_font: function(font) {
  // check if font exists
  font = Pointer_stringify(font);
  var font_test_node = vimjs.font_test_node;
  font_test_node.innerHTML = 'the quick brown fox jumps over the lazy dog';

  return ['serif', 'sans-serif', 'monospace'].some(function(base_font) {
    font_test_node.style.font = font + ',' + base_font;
    // override existing definition of font size
    font_test_node.style.fontSize = '64px';
    var w = font_test_node.clientWidth;
    var h = font_test_node.clientHeight;

    font_test_node.style.font = '64px ' + base_font;
    return (font_test_node.clientWidth != w) || (font_test_node.clientHeight != h);
  });
},

vimjs_get_char_width: function() {
  return vimjs.char_width;
},
vimjs_get_char_height: function() {
  return vimjs.char_height;
},

vimjs_is_valid_color: function(colorp) {
  var color = Pointer_stringify(colorp);
  return /(^#[0-9A-F]{6}$)|(^#[0-9A-F]{3}$)/i.test(color)
    || (color.toLowerCase() in vimjs.color_map);
},
vimjs_get_rgb: function (string) {
  string = Pointer_stringify(string);
  string = string.toLowerCase();
  // https://github.com/harthur/color-string
  // MIT License
  var abbr = /^#([a-fA-F0-9]{3})$/;
  var hex = /^#([a-fA-F0-9]{6})$/;

  var rgb = [0, 0, 0];
  var match = string.match(abbr);
  if (match) {
    match = match[1];
    for (var i = 0; i < rgb.length; i++) {
      rgb[i] = parseInt(match[i] + match[i], 16);
    }
  } else if (match = string.match(hex)) {
    match = match[1];
    for (var i = 0; i < rgb.length; i++) {
      rgb[i] = parseInt(match.slice(i * 2, i * 2 + 2), 16);
    }
  } else {
    var builtin_rgb = vimjs.color_map[string];
    if(builtin_rgb)
      rgb = builtin_rgb;
  }
  var ret = 0;
  for (var i = 0; i < rgb.length; i++) {
    ret = (ret << 8) + rgb[i];
  }
  return ret;
},
vimjs_set_fg_color: function(color) {
  vimjs.fg_color = vimjs.get_color_string(color);
},
vimjs_set_bg_color: function(color) {
  vimjs.bg_color = vimjs.get_color_string(color);
},
vimjs_set_sp_color: function(color) {
  vimjs.sp_color = vimjs.get_color_string(color);
},

vimjs_print_stacktrace: function() {
  console.log((new Error).stack);
},

vimjs_call_shell: function(cmd, options) {
  cmd = Pointer_stringify(cmd);
  try {
    try {
      // the cmd may be a JavaScript snippet
      eval(cmd);
    } catch (e) {
      if(e instanceof SyntaxError) {
        // try to execute a file
        try {
          var content = FS.readFile(cmd.replace(/(^\s+|\s+$)/g, ''), { encoding: 'utf8'} );
        } catch(e1) {
          // cannot find file, throw the old Error
          throw e;
        }
        eval(content);
      } else {
        // not a SyntaxError, process it outside
        throw e;
      }
    }
  } catch (e) {
    if (e instanceof Error) {
      console.log(e.name + ': ' + e.message);
    } else {
      console.log('Exception thrown: ', e);
    }
  }
}, 

vimjs_browse__dep: ['$vimjs', 'emscripten_async_resume'],
vimjs_browse: function(buf, buf_size, saving, default_name, init_dir) {
  asm['setAsync']();
    default_name = Pointer_stringify(default_name);
    if(default_name === 'local' && window.FileReader) { 
      if(saving) {
        // TODO: save to local 
        setTimeout(_emscripten_async_resume, 1);
      } else {
        vimjs.load_local_file(_emscripten_async_resume, buf);
      }
    } else if (default_name === 'dropbox') {
      if(saving) {
        vimjs.ensure_dropbox(function() {
          vimjs.save_dropbox_file(_emscripten_async_resume, buf);
        });
      } else {
        vimjs.ensure_dropbox(function() {
          vimjs.load_dropbox_file(_emscripten_async_resume, buf);
        });
      }
    } else {
      vimjs.load_nothing(_emscripten_async_resume, buf);
    }
  },

  vimjs_haskey: function(name) {
    name = Pointer_stringify(name, 2);
    return (name in vimjs.special_keys_namemap);
  },

  vimjs_dummy__: null,
};
autoAddDeps(LibraryVIM, '$vimjs');
mergeInto(LibraryManager.library, LibraryVIM);
