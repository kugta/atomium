<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_breadcrumb() {
  return array(
    'breadcrumb' => array(
      'variables' => array('breadcrumb' => NULL),
      'template' => 'breadcrumb',
    ),
  );
}

/**
 * Implements hook_atomium_definition_HOOK().
 */
function atomium_atomium_definition_breadcrumb() {
  return array(
    'label' => 'Breadcrumb',
    'description' => 'Site breadcrumb.',
    'preview' => array(
      'breadcrumb' => array(
        l(t('Home'), '/'),
        l(t('News'), '/'),
        t('My news title'),
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_breadcrumb(&$variables, $hook) {
  $links = array();
  foreach ($variables['breadcrumb'] as $key => $item) {
    if (is_string($item)) {
      $item = array(
        '#markup' => $item,
      );
    }
    $item += array(
      '#theme_wrappers' => array('html_tag'),
      '#tag' => 'li',
    );

    $links[] = $item;
  }

  $variables['wrapper_attributes_array'] = $variables['attributes_array'];

  $variables[$hook] = '';
  if ($links) {
    $variables[$hook] = array(
      $hook => array(
        '#theme' => array('item_list'),
        '#items' => $links,
        '#type' => 'ul',
        '#wrapper' => FALSE,
        '#attributes' => $variables['attributes_array'],
      ),
      '#theme_wrappers' => array('html_tag'),
      '#tag' => 'nav',
      '#attributes' => $variables['wrapper_attributes_array'],
    );
  }
}
