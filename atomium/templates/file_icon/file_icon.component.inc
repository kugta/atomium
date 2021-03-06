<?php

/**
 * @file
 * Contains component file.
 */

/**
 * Implements hook_atomium_theme_HOOK().
 */
function atomium_atomium_theme_file_icon() {
  return array(
    'file_icon' => array(
      'template' => 'file-icon',
      'variables' => array(
        'file' => NULL,
        'icon_directory' => NULL,
        'alt' => '',
      ),
    ),
  );
}

/**
 * Implements hook_preprocess_HOOK().
 */
function atomium_preprocess_file_icon(&$variables, $hook) {
  $file = $variables['file'];

  if (isset($file->filemime)) {
    $mimetype = drupal_html_class($file->filemime);
    // TODO: Add this to the #theme down under.
    $variables['theme_hook_suggestions'][] = $variables['theme_hook_original'] . '__' . $mimetype;
  }

  $variables['attributes_array']['class'][] = 'file-icon';
  $variables[$hook] = array(
    $hook => array(
      '#theme' => array('image'),
      '#attributes' => $variables['attributes_array'],
      '#alt' => check_plain($variables['alt']),
      '#title' => isset($file->filemime) ? check_plain($file->filemime) : NULL,
      '#path' => file_icon_url($file, $variables['icon_directory']),
    ),
  );
}
