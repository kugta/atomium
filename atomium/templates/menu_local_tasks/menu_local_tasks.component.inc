<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_menu_local_tasks() {
  return array(
    'menu_local_tasks' => array(
      'template' => 'menu-local-tasks',
      'variables' => array(
        'primary' => array(),
        'secondary' => array(),
        'primary_attributes_array' => array(),
        'secondary_attributes_array' => array(),
        'type' => 'ul',
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_menu_local_tasks(&$variables, $hook) {
  $variables['primary_attributes_array'] = $variables['attributes_array'];
  $variables['secondary_attributes_array'] = $variables['attributes_array'];

  $variables['primary_attributes_array']['class'][] = 'hook__' . $hook . '__primary';
  $variables['secondary_attributes_array']['class'][] = 'hook__' . $hook . '__secondary';

  if ($variables['primary']) {
    $variables['primary'] = array(
      '#theme' => array('item_list__' . $variables['theme_hook_original'] . '__primary'),
      '#items' => $variables['primary'],
      '#type' => $variables['type'],
      '#attributes' => $variables['primary_attributes_array'],
      '#wrapper_attributes' => array(),
    );
  }

  if ($variables['secondary']) {
    $variables['secondary'] = array(
      '#theme' => array('item_list__' . $variables['theme_hook_original'] . '__secondary'),
      '#items' => $variables['secondary'],
      '#type' => $variables['type'],
      '#attributes' => $variables['secondary_attributes_array'],
      '#wrapper_attributes' => array(),
    );
  }
}
