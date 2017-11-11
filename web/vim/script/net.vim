" Javascript wrap
function! ReadDoc(file)
    " Function to load a file in mem

  	" Get current path/file
	if (a:file[0] == "/")
	  let l:path = "/" . "".join(split(a:file, "/")[:-2], "/")
	  let l:file = split(a:file, "/")[-1] 
	else
	  let l:path = expand("%:p:h")
	  let l:file = a:file
	endif

  	" Load file
	let l:cmd =  '!tin_load("' .l:path."/".l:file . '")' 

	" Edit file 
	let l:file_path = l:path . "/" . l:file
    execute  l:cmd
	execute "edit"  l:file_path

	" Debug regs
	let g:da=l:cmd
	let g:db=l:file_path
	let g:dc=l:path
	let g:dd=a:file
endfunction

function! ReadWrapper(word)
  let l:file = substitute(a:word, "|", "", "g")
  silent call ReadDoc(l:file)
endfunction

function! OpenXref(link)
	let l:cmd =  "!tin_href('" . a:link . "', '<-vim.js');"
    execute l:cmd
endfunction

function! DownloadFile()
    " Download buffer content with filename
    let l:filename = expand("%:t")
    let l:content = join(getline(1,'$'), "<tincr>")
    let l:content = substitute(l:content, "'", "<tinq1>", 'g')
    let l:content = substitute(l:content, "\\", "<tinbs>", 'g')
    let l:cmd = "!tin_download('" . l:filename. "', '" . l:content . "');"
    silent execute l:cmd
endfunction

function! Url(path, url)
  " Full path full url
  let l:cmd = '!tin_url("'
  let l:cmd .= a:path
  let l:cmd .= '", "'
  let l:cmd .= a:url
  let l:cmd .= '");'
  echom "Url cmd: " . l:cmd
  execute l:cmd
endfunction
