const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')
const UglifyJSPlugin = require('uglifyjs-webpack-plugin')
const CopyWebpackPlugin = require('copy-webpack-plugin')
const isProduction = process.env.NODE_ENV === 'production'

const outputDir = path.join(__dirname, '../dist')

module.exports = {
    mode: isProduction
        ? 'production'
        : 'development',
    entry: {
        main: path.join(__dirname, '../app/app.js')
    },
    output: {
        path: outputDir,
        filename: '[name].js'
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                exclude: path.join(__dirname, '../node_modules'),
                use: [ 'babel-loader' ]
            },
            {
                test: /\.css$/,
                use: [ 'css-loader' ]
            }
        ]
    },
    resolve: {
        alias: {
            '@': path.join(__dirname, '../')
        },
        extensions: [ '*', '.js', '.ts', '.json' ]
    },
    devtool: isProduction
        ? 'none'
        : 'cheap-eval-source-map',
    optimization: {
        minimize: isProduction,
        minimizer: [
            new UglifyJSPlugin({
                cache: true,
                parallel: true,
                sourceMap: true
            })
        ]
    },
    plugins: [
        new CopyWebpackPlugin({
            patterns: [
                {
                    from: path.join(__dirname, '../vendor'),
                    to: path.join(outputDir, 'vendor')
                },
                {
                    from: path.join(__dirname, '../static'),
                    to: path.join(outputDir, 'static')
                }
            ]
        }),
        new HtmlWebpackPlugin({
            template: path.join(__dirname, '../index.html'),
            filename: 'index.html',
            env: process.env.NODE_ENV
        })
    ]
}