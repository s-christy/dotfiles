" All system-wide defaults are set in $VIMRUNTIME/debian.vim and sourced by
" the call to :runtime you can find below.  If you wish to change any of those
" settings, you should do it in this file (/etc/vim/vimrc), since debian.vim
" will be overwritten everytime an upgrade of the vim packages is performed.
" It is recommended to make changes after sourcing debian.vim since it alters
" the value of the 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Vim will load $VIMRUNTIME/defaults.vim if the user does not have a vimrc.
" This happens after /etc/vim/vimrc(.local) are loaded, so it will override
" any settings in these files.
" If you don't want that to happen, uncomment the below line to prevent
" defaults.vim from being loaded.
" let g:skip_defaults_vim = 1

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
"set compatible

" Vim5 and later versions support syntax highlighting. Uncommenting the next
" line enables syntax highlighting by default.
syntax on

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"if has("autocmd")
"  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
"endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
"if has("autocmd")
"  filetype plugin indent on
"endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
set showcmd		" Show (partial) command in status line.
set showmatch		" Show matching brackets.
set ignorecase		" Do case insensitive matching
"set smartcase		" Do smart case matching
"set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
"set hidden		" Hide buffers when they are abandoned
set mouse=a		" Enable mouse usage (all modes)

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif





"Begin User written code





:set nocompatible
filetype plugin on
:set nu
highlight RED ctermbg=red guibg=red
:let m=matchadd("RED","TODO")
":let m=matchadd("RED",'\%81v')
:let m=matchadd("RED",'\s\+$')
:nmap <up> ddkP
:nmap <down> ddp

:map J 5j
:map K 5k

set nowrap

:map <F2> :set list!<CR>
:map <F3> <C-R>=strftime("%Y-%m-%d %a %I:%M %p")<CR>
:map <F4> :set wrap!<CR><Esc>
nnoremap <f5> :w<CR> :!python3 -Bi %<cr>
":map <F5> :setlocal spell! spelllang=en_us<CR>
":map <F6> :r ~/s-christy/dotfiles/filler\ text<CR><Esc>
:map <F6> :w<CR>:!./do<CR>
":map <F7> :set ve=all<CR><Esc>:echo "ve set to all"<CR><Esc>
:map <F7> :map j jzz<CR> :map k kzz<CR>
:map <F8> :changes<CR>
:map <F9> :set mouse=""<CR>:set nu!<CR>
:map <F10> ggVGg?
:map <F11> :inoremap [ <Space>
:map <F12> :source ~/.vimrc<CR><Esc>:echo "reloaded .vimrc"<CR><Esc>
:set listchars+=space:␣

"autoindent C programs
"nmap F gg=G

nmap <F3> i<C-R>=strftime("%Y-%m-%d %a %I:%M %p")<CR><Esc>
imap <F3> <C-R>=strftime("%Y-%m-%d %a %I:%M %p")<CR>

:noremap <F1> :echo "F2 set list!\nF3 print time\nF4 toggle wrap\nF5 spellcheck\nF6 insert filler text\nF7 set ve\nF8 show changes\nF9 disable mouse select\nF10 obscure file\nF11 [ mapped to <Space>\nF12 reload .vimrc"<Esc>

:map <Space><Space> <Esc>/<++><CR>xxxxi
:map ;+ <Esc>i<++>
:map ;remtrails :%s/ $//g<CR>

"you can use :tab help topic instead of :help topic

"fullscreens the help window
:set helpheight=120

"fuck you java
imap ;print System.out.println("");

imap ;pa <ESC>"*p

set hlsearch

noremap ; :


set foldmethod=syntax
set tabstop=4

"you can autocenter using :map j jzz and :map k kzz. This doesn't slow things
"down apparently

"imap ( ()<LEFT>
"imap [ []<LEFT>
"imap { {}<LEFT>
"imap " ""<LEFT>

