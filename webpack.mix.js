/*
 * __/\\\\\\\\\\\\\\\__/\\\\____________/\\\\__/\\\\\\\\\\\\\\\_
 *  _\/\\\///////////__\/\\\\\\________/\\\\\\_\///////\\\/////__
 *   _\/\\\_____________\/\\\//\\\____/\\\//\\\_______\/\\\_______
 *    _\/\\\\\\\\\\\_____\/\\\\///\\\/\\\/_\/\\\_______\/\\\_______
 *     _\/\\\///////______\/\\\__\///\\\/___\/\\\_______\/\\\_______
 *      _\/\\\_____________\/\\\____\///_____\/\\\_______\/\\\_______
 *       _\/\\\_____________\/\\\_____________\/\\\_______\/\\\_______
 *        _\/\\\\\\\\\\\\\\\_\/\\\_____________\/\\\_______\/\\\_______
 *         _\///////////////__\///______________\///________\///________
 */

const mix = require('laravel-mix');
const tailwindcss = require('tailwindcss')('./tailwind.config.js');

// Add TypeScript support.
mix.webpackConfig(
    {
        module: {
            rules: [
                {
                    test: /\.tsx?$/,
                    loader: 'ts-loader',
                    exclude: /node_modules/
                }
            ]
        }
    }
);

/*
 |--------------------------------------------------------------------------
 | Mix Asset Management
 |--------------------------------------------------------------------------
 |
 | Mix provides a clean, fluent API for defining some Webpack build steps
 | for your application. By default, we are compiling the CSS
 | file for the application as well as bundling up all the JS files.
 |
 */

mix
    .sass(
        './scss/global.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    )
    .sass(
        './scss/std_nav.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    )
    .sass(
        './scss/std_table.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    )
    .sass(
        './scss/std_form.scss',
        './css'
    )
    .options(
        {
            processCssUrls: false,
            postCss: [
                tailwindcss
            ]
        }
    );

// Concatenate all CSS assets together.
mix.styles(
    [
        './css/global.css',
        './css/std_nav.css',
        './css/std_table.css',
        './css/std_form.css'
    ],
    './css/global.css'
);

// Typescript compilation.
mix.js('./ts/global.ts', './js/global.js');
