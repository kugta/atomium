<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_form() {
  return array(
    'form' => array(
      'render element' => 'element',
      'template' => 'form',
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_form(&$variables) {
  $variables['theme_hook_suggestions'][] = 'form--' . $variables['element']['#form_id'];

  $element = &$variables['element'];

  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }

  $variables['attributes_array'] = drupal_array_merge_deep($variables['attributes_array'], $element['#attributes']);
}
