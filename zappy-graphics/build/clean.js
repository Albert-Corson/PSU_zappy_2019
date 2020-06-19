const rm = require('rimraf')
const chalk = require('chalk')
const config = require('./webpack.config')

rm(config.output.path, error => {
    if (error) {
        console.erro(chalk.bold.red('[!] Clean failed.\n'))
        console.erro(error)
        process.exit(1)
    }
    console.log(chalk.bold.green(`[?] Clean complete.\n`))
})