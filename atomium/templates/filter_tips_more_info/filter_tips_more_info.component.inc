<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_filter_tips_more_info() {
  return array(
    'filter_tips_more_info' => array(
      'template' => 'filter-tips-more-info',
      'variables' => array(
        'link' => array(),
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_filter_tips_more_info(&$variables, $hook) {
  $variables[$hook] = array(
    $hook => array(
      '#theme' => array('link'),
      '#text' => t('More information about text formats'),
      '#path' => 'filter/tips',
      '#options' => array('attributes' => array('target' => '_blank')),
    ),
  );
}
