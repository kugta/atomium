<?php

namespace Drupal\Tests\atomium\Kernel;

/**
 * Class AbstractThemeTest.
 *
 * @package Drupal\Tests\atomium\Kernel
 */
abstract class AbstractThemeTest extends AbstractKernelTest {

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    global $theme_engine;
    global $conf;

    $conf['theme_debug'] = FALSE;
    $theme_engine = 'atomium_test';
  }

}
