

vimfx.addCommand({
	name: 'test',
	description: "don't need no description",
}, () => {
	console.log('test')
})
vimfx.set('custom.mode.normal.test','gm')

//toggles ignore mode with i in addition to shift-escape
MAPPINGS = {
    'exit': ['<i>', 'mode.ignore'],
},
Object.entries(MAPPINGS).forEach(([command, value]) => {
    let [shortcuts, mode] = Array.isArray(value)
        ? value
        : [value, 'mode.normal']
    vimfx.set(`${mode}.${command}`, shortcuts)
})

// ctrl-shift-j opens developer console in firefox
// gB will open a dialogue to blacklist certain sites
// you can use wildcards here (*)
// https://pastebin.com/ytw9tH63
