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

import * as $ from 'jquery';
import * as _ from 'lodash';

(<any>window).$ = $;
(<any>window)._ = _;

/**
 * Register an event listener in global scope to mark the appropriate nav bar link as the page being currently
 * viewed.
 */
$(function ()
{
    let navLinks : JQuery = $('li.global_nav_destination a');
    _.each(navLinks, function (navLink : HTMLElement)
    {
        let $navLink : JQuery = $(navLink);
        if (window.location.pathname === $navLink.attr('href'))
        {
            $navLink.parent('li').addClass('global_nav_destination_active');
        }
    });
});
