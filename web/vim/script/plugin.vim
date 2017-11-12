" Pluggin dit
let g:d_plugin = {}
" AnsiEscape
let g:d_plugin["ansiesc"] = ["https://github.com/powerman/vim-plugin-AnsiEsc"]
call add(g:d_plugin["ansiesc"], "plugin/AnsiEscPlugin.vim")
call add(g:d_plugin["ansiesc"], "autoload/AnsiEsc.vim")
call add(g:d_plugin["ansiesc"], "plugin/cecutil.vim")

" Airline
let g:d_plugin["airline"] = ["https://github.com/vim-airline/vim-airline"]
call add(g:d_plugin["airline"], "plugin/airline.vim")
call add(g:d_plugin["airline"], "autoload/airline.vim")

call add(g:d_plugin["airline"], "autoload/airline/section.vim")
call add(g:d_plugin["airline"], "autoload/airline/async.vim")
call add(g:d_plugin["airline"], "autoload/airline/util.vim")
call add(g:d_plugin["airline"], "autoload/airline/parts.vim")
call add(g:d_plugin["airline"], "autoload/airline/themes.vim")
call add(g:d_plugin["airline"], "autoload/airline/themes")
call add(g:d_plugin["airline"], "autoload/airline/highlighter.vim")
call add(g:d_plugin["airline"], "autoload/airline/msdos.vim")
call add(g:d_plugin["airline"], "autoload/airline/debug.vim")
call add(g:d_plugin["airline"], "autoload/airline/extensions.vim")
call add(g:d_plugin["airline"], "autoload/airline/builder.vim")
call add(g:d_plugin["airline"], "autoload/airline/init.vim")

call add(g:d_plugin["airline"], "autoload/airline/themes/dark.vim")
call add(g:d_plugin["airline"], "autoload/airline/extensions/default.vim")

" CtrlP
let g:d_plugin["ctrlp"] = ["https://github.com/kien/ctrlp.vim"]
call add(g:d_plugin["ctrlp"], "plugin/ctrlp.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/mixed.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/buffertag.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/line.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/utils.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/dir.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/bookmarkdir.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/quickfix.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/changes.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/rtscript.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/mrufiles.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/tag.vim")
call add(g:d_plugin["ctrlp"], "autoload/ctrlp/undo.vim")

" Nerdtree
let g:d_plugin["nerdtree"] = ["https://github.com/scrooloose/nerdtree"]

" Rainbow Parenthesis
let g:d_plugin["rainbow_parenthesis"] = ["https://github.com/kien/rainbow_parentheses.vim"]
call add(g:d_plugin["rainbow_parenthesis"], "plugin/rainbow_parentheses.vim")
call add(g:d_plugin["rainbow_parenthesis"], "autoload/rainbow_parentheses.vim")

" Easy Motion
" TODO finish the big tree
let g:d_plugin["easymotion"] = ["https://github.com/easymotion/vim-easymotion"]
call add(g:d_plugin["easymotion"], "plugin/EasyMotion.vim")
call add(g:d_plugin["easymotion"], "autoload/vital.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/cmigemo.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/highlight.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/sticky_table.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/migemo/eucjp.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/migemo/utf8.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/migemo/cp932.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/overwin.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/helper.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/command_line.vim")
call add(g:d_plugin["easymotion"], "autoload/EasyMotion/undo.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/easymotion.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Input.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/String.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Exception.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Signals.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Keymapping.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Base.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/Delete.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/History.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/CursorMove.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/Paste.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/ExceptionMessage.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/DrawCommandline.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/ExceptionExit.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/NoInsert.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/Cancel.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/KeyMapping.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/BufferComplete.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/Redraw.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/Exit.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/InsertRegister.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Over/Commandline/Modules/Doautocmd.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Data/Set.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Data/Dict.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Data/List.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Palette/Capture.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Palette/Keymapping.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Palette/Highlight.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/HitAHint")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/HitAHint/Hint.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/HitAHint/Motion.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Prelude.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Vim/Guard.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Vim/Buffer.vim")
call add(g:d_plugin["easymotion"], "autoload/vital/_easymotion/Vim/Message.vim")

" UndoTree (Gundo requires python)
let g:d_plugin["undotree"] = ["https://github.com/mbbill/undotree"]
call add(g:d_plugin["undotree"], "plugin/undotree.vim")
call add(g:d_plugin["undotree"], "autoload/undotree.vim")
call add(g:d_plugin["undotree"], "syntax/undotree.vim")


" Vim Script
" CamelCaseMotion
let g:d_plugin["camelcasemotion"] = ["https://github.com/vim-scripts/camelcasemotion"]
call add(g:d_plugin["camelcasemotion"], "plugin/camelcasemotion.vim")
call add(g:d_plugin["camelcasemotion"], "autoload/camelcasemotion.vim")

" DelimitMate
let g:d_plugin["delimitMate"] = ["https://github.com/Raimondi/delimitMate"]
call add(g:d_plugin["delimitMate"], "plugin/delimitMate.vim")
call add(g:d_plugin["delimitMate"], "autoload/delimitMate.vim")

" Matchit
let g:d_plugin["matchit"] = ["https://github.com/vim-scripts/matchit.zip"]
call add(g:d_plugin["matchit"], "plugin/matchit.vim")


" TPOPE
" Surround
let g:d_plugin["surround"] = ["https://github.com/tpope/vim-surround"]
call add(g:d_plugin["surround"], "plugin/surround.vim")

" Commentray
let g:d_plugin["commentary"] = ["https://github.com/tpope/vim-commentary"]
call add(g:d_plugin["commentary"], "plugin/commentary.vim")

" Unimpaired
let g:d_plugin["unimpaired"] =["https://github.com/tpope/vim-unimpaired"]
call add(g:d_plugin["unimpaired"], "plugin/unimpaired.vim")

" Abolish
let g:d_plugin["abolish"] = ["https://github.com/tpope/vim-abolish"]
call add(g:d_plugin["abolish"], "plugin/abolish.vim")

" Repeat
let g:d_plugin["repeat"] = ["https://github.com/tpope/vim-repeat"]
call add(g:d_plugin["repeat"], "autoload/repeat.vim")

" TPOPE END

" End
let g:d_plugin["none"] = ["nothing"]

function! LoadPlugin(name)
    " Load plugin if name in a list
    echom "Loading Plugin: " . a:name
    let l:index = index(keys(g:d_plugin), a:name)
    if (index == -1) | ret | endif

    " Let path
    let l:out_path = '/vim/plugin/' . a:name . "/"

    " Create dir
    let l:cmd = '!Module["FS_createPath"]("/vim/plugin", "'
    let l:cmd .= a:name . '", true, true);'
    silent execute l:cmd
    let l:cmd_p = '!Module["FS_createPath"]("/vim/plugin/' . a:name . '", '
    let l:cmd_p .= '"plugin", true, true);'
    silent execute l:cmd_p
    let l:cmd_a = '!Module["FS_createPath"]("/vim/plugin/' . a:name . '", '
    let l:cmd_a .= '"autoload", true, true);'
    silent execute l:cmd_a
    

    " Download Raw files
    let l:d_list = g:d_plugin[a:name]
    let l:url = l:d_list[0]
    call remove(l:d_list, 0)
    let l:sub_path1 = ""
    for l:sub_path in l:d_list
      if (l:sub_path1 == "")
        let l:sub_path1 = l:sub_path
      endif
      let l:cmd2 = '!tin_url("'
      let l:cmd2 .= l:out_path . l:sub_path
      let l:cmd2 .= '", "'
      let l:cmd2 .= substitute(l:url, 'github.com', 'raw.githubusercontent.com', '')
      let l:cmd2 .= '/master/'
      let l:cmd2 .= l:sub_path
      let l:cmd2 .= '");'
      echom "Cmd2: " . l:cmd2
      silent execute l:cmd2
      if (match(l:sub_path, "syntax/") == 0)
        execute "source " . l:out_path . l:sub_path
      endif
    endfor

    " Runtime path
    let &runtimepath.=",/vim/plugin/" . a:name

	" Source plugin
    echo "Sourcing plugin: " . l:sub_path1
    execute "source " . l:out_path . l:sub_path1


endfunction

function! CompletePlugin(ArgLead, CmdLine, CursorPos)
  let l:plugin = keys(g:d_plugin)
  let l:res = []
  for l:elt in l:plugin
   if (match(l:elt, a:ArgLead) != -1)
     call add(l:res, l:elt)
   endif
  endfor
  return l:res
endfunction


command! -nargs=1 -complete=customlist,CompletePlugin Plug call LoadPlugin(<q-args>)

" AnsiEscape autocommands
au BufEnter *.a.txt echom "Loading ansiesc" | call LoadPlugin("ansiesc")| set nowrap | echom "I saw an ansi file"
au BufWinEnter *.a.txt AnsiEsc
au ColorScheme *.a.txt AnsiEsc!
