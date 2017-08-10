

vimfx.addCommand({
	name: 'test',
	description: "don't need no description",
}, () => {
	console.log('test')
})
vimfx.set('custom.mode.normal.test','gm')

// ctrl-shift-j opens developer console in firefox
