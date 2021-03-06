<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_more_link() {
  return array(
    'more_link' => array(
      'render element' => 'element',
      'template' => 'more-link',
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_more_link(&$variables, $hook) {
  $variables[$hook] = array(
    $hook => array(
      '#theme' => array('link'),
      '#text' => t('More'),
      '#path' => $variables['url'],
      '#options' => array('attributes' => array('title' => $variables['title'])),
    ),
    '#theme_wrappers' => array('container'),
    '#attributes' => $variables['attributes_array'],
  );
}
