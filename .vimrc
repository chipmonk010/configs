set nocompatible
set encoding=utf-8
syntax on

set tabstop=2
set shiftwidth=2
set softtabstop=2
set textwidth=80
set noautoindent
set nosmartindent
set background=dark
set novb									" don't beep
set t_vb=
set foldenable					" allow folding code
set foldmethod=marker		" marks foldstarts/ends with {{{ }}}
set hlsearch						" highlight all search results
set incsearch						" increment search
set ignorecase					" case-insensitive search
set smartcase						" upper-case sensitive search
set backspace=indent,eol,start
set history=100					" 100 lines of command line history
set cmdheight=1					" command line height
set ruler								" ruler display in status line
set showmode						" show mode at bottom of screen
set number							" show line numbers
set nobackup						" disable backup files (filename~)
set showmatch						" show matching brackets (),{},[]
set whichwrap=h,l,<,>,[,]
set showcmd
set modeline
set wildmenu
set splitbelow
set formatoptions+=l
set selection=inclusive
set autowrite
set cinoptions=g0,:0,l1,(0,t0
set shortmess=a
set complete=.,t,i,b,w,k
set wildchar=<tab>
set wildmenu
set wildmode=longest:full,full
set previewheight=5

" MS Word document reading
au BufReadPre *.doc set ro
au BufReadPre *.doc set hlsearch!
au BufReadPost *.doc %!antiword "%"

" Disables autocomment for all files
au FileType * setl fo-=cro

"	Enable printing to Postscript with :ha afile.ps
" :ha		prints normalally 
let &printexpr="(v:cmdarg=='' ? ".
    \"system('lpr' . (&printdevice == '' ? '' : ' -P' . &printdevice)".
    \". ' ' . v:fname_in) . delete(v:fname_in) + v:shell_error".
    \" : system('mv '.v:fname_in.' '.v:cmdarg) + v:shell_error)"

" color scheme stuff
"let g:gardener_transbg=1

if (&term == 'rxvt')
	set t_Co=256
endif

if (&t_Co == 256)
	colorscheme gardener
endif

if has('gui_running')
	set t_Co=256
	colorscheme inkpot
endif
