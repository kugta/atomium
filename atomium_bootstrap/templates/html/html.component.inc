<?php

/**
 * @file
 * Html.preprocess.inc.
 */

/**
 * Implements hook_preprocess_html().
 */
function atomium_bootstrap_preprocess_html(&$variables, $hook) {
  drupal_add_js('https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js', 'external');
  drupal_add_css('https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css', 'external');
}
