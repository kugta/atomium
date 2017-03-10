<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_bootstrap_preprocess_region(&$variables, $hook) {
  if (strpos($variables['elements']['#region'], 'sidebar') !== FALSE) {
    $variables[$hook]['#attributes']['class'][] = 'col-md-3';
  }
}