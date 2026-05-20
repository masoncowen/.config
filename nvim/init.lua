vim.o.number = true
vim.o.relativenumber = false
vim.o.signcolumn = 'yes'
vim.o.tabstop = 2
vim.o.shiftwidth = 2
vim.o.expandtab = true
vim.o.wrap = false
vim.o.hlsearch = false
vim.o.smartcase = true
vim.o.ignorecase = true
vim.o.mouse = 'nvi'
vim.o.swapfile = false
vim.o.completeopt = 'menu,menuone,noinsert'
vim.cmd.colorscheme('habamax')

vim.keymap.set('n', 'H', function() vim.cmd('lefta vsplit') end)
vim.keymap.set('n', 'J', function() vim.cmd('below split') end)
vim.keymap.set('n', 'K', function() vim.cmd('above split') end)
vim.keymap.set('n', 'L', function() vim.cmd('rightb vsplit') end)
vim.keymap.set('n', 'ZJ', 'J')

vim.pack.add({'https://github.com/nvim-mini/mini.surround'})
require('mini.surround').setup()
vim.pack.add({'https://github.com/nvim-mini/mini.comment'})
require('mini.comment').setup()

vim.pack.add({'https://github.com/gbprod/substitute.nvim'})
require('substitute').setup()
vim.keymap.set("n", "s", require('substitute').operator, { noremap = true })
vim.keymap.set("n", "ss", require('substitute').line, { noremap = true })
vim.keymap.set("n", "S", require('substitute').eol, { noremap = true })
vim.keymap.set("x", "s", require('substitute').visual, { noremap = true })
