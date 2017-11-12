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
call add(g:d_plugin["easymotion"], "autoload/rainbow_parenthesis.vim")

" UndoTree (Gundo requires python)
" TODO manage syntax
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
      echom "Cmd2: " . l:cmd2 . ", " . l:sub_path
      silent execute l:cmd2
      if (match(l:sub_path, "autoload/") == 0)
        echo "Sourcing autoload: " . l:sub_path
        execute "source " . l:out_path . l:sub_path
      endif
    endfor

    echo "Sourcing plugin: " . l:sub_path1
    execute "source " . l:out_path . l:sub_path1

    " Runtime path
    let &runtimepath.=",/vim/plugin/" . a:name

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
