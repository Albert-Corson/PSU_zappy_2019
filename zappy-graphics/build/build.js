const chalk = require('chalk')
const webpack = require('webpack')
const config = require('./webpack.config')

webpack(config, (error, stats) => {
    if (stats.hasErrors()) {
        console.error(chalk.bold.red('[!] Build failed.\n'))
        process.stdout.write(stats.toString({
            colors: true,
            modules: false,
            children: false,
            chunks: false,
            chunkModules: false
        }) + '\n\n')
        process.exit(1)
    }
    console.log(chalk.bold.green('[?] Build complete.\n'))
})