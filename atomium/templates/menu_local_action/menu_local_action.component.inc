<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_menu_local_action() {
  return array(
    'menu_local_action' => array(
      'render element' => 'element',
      'template' => 'menu-local-action',
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_menu_local_action(&$variables, $hook) {
  $link = $variables['element']['#link'];

  $link += array('localized_options' => array());
  $link['localized_options'] += array('attributes' => array());
  $options = drupal_array_merge_deep($link['localized_options']['attributes'], $variables['attributes_array']);

  if (isset($link['href'])) {
    $variables[$hook] = array(
      '#theme' => array('link'),
      '#text' => $link['title'],
      '#path' => $link['href'],
      '#options' => $options,
    );
  }
  elseif (!empty($link['localized_options']['html'])) {
    $variables[$hook] = $link['title'];
  }
  else {
    $variables[$hook] = check_plain($link['title']);
  }
}
