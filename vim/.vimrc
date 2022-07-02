"Vim-Plug
let data_dir = has('nvim') ? stdpath('data') . '/site' : '~/.vim'
if empty(glob(data_dir . '/autoload/plug.vim'))
  silent execute '!curl -fLo '.data_dir.'/autoload/plug.vim --create-dirs https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
endif
autocmd VimEnter * if len(filter(values(g:plugs), '!isdirectory(v:val.dir)'))
  \| PlugInstall --sync | source $MYVIMRC
\| endif

call plug#begin()
Plug 'vimwiki/vimwiki'
Plug 'junegunn/goyo.vim'
Plug 'junegunn/limelight.vim'
Plug 'tpope/vim-surround'
Plug 'tpope/vim-sensible'
Plug 'tpope/vim-unimpaired'
Plug 'tpope/vim-commentary'
Plug 'tpope/vim-endwise'
Plug 'tpope/vim-markdown'
call plug#end()

"Vimwiki recommended
set nocompatible
filetype plugin on

"Visual options
syntax on
set nu ruler
set mouse=a
colorscheme industry

"Tabs
set autoindent smartindent smarttab expandtab
set shiftwidth=2 tabstop=2 softtabstop=2

"Swap files and Backups
set noswapfile
set nobackup
set nowritebackup
set undodir=~/.vim/undodir
set undofile

"Basic mappings
nmap Y y$
nnoremap <CR> o<ESC>
nnoremap <S-CR> o<esc>
map <M-SPACE> <ESC>
map <silent> !. !!sh<CR>

"Leader mappings
let mapleader=" "
nmap <leader>s :w<cr>
nmap <leader>z ZZ
nmap <leader>q ZQ
nmap <silent> <leader>r :source $VIM_CONFIG<cr>:echo 'Reloaded'<cr>

"less basic mappings
nnoremap ci/ t/ct/
nnoremap ca/ f/cf/
nnoremap <leader>c :!viCompile ~/writing/diss/diss.tex <cr><cr>

"Tmux integrations
autocmd BufReadPost,FileReadPost,BufNewFile,BufEnter * call system("tmux rename-window 'vim|" . expand("%:t") . "'")
autocmd VimLeave * call system("tmux setw automatic-rename")
