<?php

/**
 * @file
 * Breadcrumb.preprocess.inc.
 */

/**
 * Implements hook_preprocess_breadcrumb().
 */
function atomium_foundation_preprocess_breadcrumb(&$variables, $hook) {
  $variables[$hook]['#attributes'] = array(
    'class' => array(
      'breadcrumbs',
    ),
    'rel' => 'navigation',
    'role' => 'navigation',
    'aria-label' => t('You are here'),
  );
  $variables[$hook][$hook]['#attributes']['class'][] = 'no-bullet';
}
