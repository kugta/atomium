<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_update_status_label() {
  return array(
    'update_status_label' => array(
      'template' => 'update-status-label',
      'variables' => array('status' => NULL),
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_update_status_label(&$variables, $hook) {
  $text = '';
  $class = '';
  switch ($variables['status']) {
    case UPDATE_NOT_SECURE:
      $class = 'security-error';
      $text = t('Security update required!');
      break;

    case UPDATE_REVOKED:
      $class = 'revoked';
      $text = t('Revoked!');
      break;

    case UPDATE_NOT_SUPPORTED:
      $class = 'not-supported';
      $text = t('Not supported!');
      break;

    case UPDATE_NOT_CURRENT:
      $class = 'not-current';
      $text = t('Update available');
      break;

    case UPDATE_CURRENT:
      $class = 'current';
      $text = t('Up to date');
      break;

  }
  $variables['attributes_array']['class'][] = $class;
  $variables[$hook] = $text;
}
