<?php

/**
 * @file
 * Breadcrumb.preprocess.inc.
 */

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_bartik_preprocess_breadcrumb(&$variables, $hook) {
  if (is_array($variables['breadcrumb'])) {
    foreach ($variables['breadcrumb']['breadcrumb']['#items'] as &$item) {
      $item['#theme_wrappers'] = array();
      $tmp[] = $item;
      $tmp[] = array(
        '#markup' => ' » ',
      );
    }
    array_pop($tmp);
    $variables['breadcrumb']['breadcrumb']['#items'] = $tmp;

    unset($variables['breadcrumb']['#theme_wrappers']);
    $variables['breadcrumb']['#tag'] = 'div';
    $variables['breadcrumb']['#attributes']['id'] = 'breadcrumb';
    $variables['breadcrumb']['breadcrumb']['#type'] = 'div';
    $variables['breadcrumb']['breadcrumb']['#attributes']['class'][] = 'breadcrumb';
  }
}
