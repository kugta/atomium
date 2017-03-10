<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_status_messages() {
  return array(
    'status_messages' => array(
      'variables' => array('display' => NULL),
      'template' => 'status-messages',
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_status_messages(&$variables, $hook) {
  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );

  $output = array();
  foreach (drupal_get_messages($variables['display']) as $type => $messages) {
    $container = array(
      'messages' => array(
        '#theme' => 'item_list__' . $variables['theme_hook_original'] . '__' . $type,
        '#title' => !empty($status_heading[$type]) ? $status_heading[$type] : '',
        '#items' => $messages,
        '#type' => 'ul',
        '#attributes' => array('class' => array()),
      ),
      '#theme_wrappers' => array('container__' . $variables['theme_hook_original'] . '__' . $type),
      '#attributes' => array(
        'class' => array(
          $type,
        ),
      ),
    );

    $output[$type] = $container;
  }

  $variables[$hook] = array(
    $hook => $output,
  );
}