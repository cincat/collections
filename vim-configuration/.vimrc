execute pathogen#infect()

set nu
set nobackup

set autoindent
set cindent

set tabstop=4
set softtabstop=4
set shiftwidth=4

set gfn=YaHei\ Consolas\ Hybrid\ 13
colorscheme desert

syntax on
filetype on
filetype plugin on
filetype indent on

"to open NERDTree with ctrl n
map <C-t> :NERDTreeToggle<CR>
map <F10> :MBEToggle<CR>
map <F11> :MBEbp<CR>
map <F12> :MBEbn<CR>

"compile different type of source code!
map <C-j> :call CompileAndRun()<CR>
func! CompileAndRun()
	exec "w"
	if &filetype=='c'
		exec "!gcc -std=gnu99 -g % -o %<"
		exec "! ./%<"
	elseif &filetype=='cpp'
		exec "!g++ % -o %<"
		exec "! ./%<"
	elseif &filetype=='java'
		exec "!javac %"
		exec "!java %<"
	elseif &filetype=='ruby'
		exec "!ruby %"
	endif
endfunc

" 定义跳出括号函数，用于跳出括号  
func SkipPair()  
	if getline('.')[col('.') - 1] == ')' || getline('.')[col('.') - 1] == ']' || getline('.')[col('.') - 1] == '"' || getline('.')[col('.') - 1] == "'" || getline('.')[col('.') - 1] == '}'  
		return "\<ESC>la"  
	else  
		return "\t"  
	endif  
endfunc  
"将tab键绑定为跳出括号  
inoremap <TAB> <c-r>=SkipPair()<CR>

"显示状态栏
set laststatus=2
set autochdir
