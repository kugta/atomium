<?php

/**
 * @file
 * block.preprocess.inc
 */

/**
 * Implements hook_preprocess_block().
 */
function atomium_foundation_preprocess_block(&$variables) {
  $variables['attributes_array']['class'] = array('clearfix');
}