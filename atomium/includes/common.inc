<?php

/**
 * @file
 * common.inc
 */

/**
 * Includes a theme file.
 *
 * @param string $theme
 *   Name of the theme to use for base path.
 * @param string $path
 *   Path relative to $theme.
 *
 * @return bool
 *   TRUE if file has been included, FALSE otherwise.
 */
function atomium_include($theme, $path) {
  static $themes = array();

  if (!isset($themes[$theme])) {
    $themes[$theme] = drupal_get_path('theme', $theme);
  }

  if ($themes[$theme] && ($file = DRUPAL_ROOT . '/' . $themes[$theme] . '/' . $path) && file_exists($file)) {
    if (is_dir($file)) {
      foreach (glob($file . '/*.{inc}', GLOB_BRACE) as $file_to_include) {
        include_once $file_to_include;
      }
    }
    if (is_file($file)) {
      include_once $file;
    }

    return TRUE;
  }

  return FALSE;
}

/**
 * Returns a list of base themes for active or provided theme.
 *
 * @param string $theme_key
 *   The machine name of the theme to check, if not set the active theme name
 *   will be used.
 * @param bool $include_theme_key
 *   Whether to append the returned list with $theme_key.
 *
 * @return array
 *   An indexed array of base themes.
 */
function _atomium_get_base_themes($theme_key = NULL, $include_theme_key = FALSE) {
  static $themes;
  if (!isset($theme_key)) {
    $theme_key = $GLOBALS['theme_key'];
  }
  if (!isset($themes[$theme_key])) {
    $themes[$theme_key] = array_unique(array_filter((array) atomium_get_theme_info($theme_key, 'base theme')));
  }
  if ($include_theme_key) {
    $themes[$theme_key][] = $theme_key;
  }
  return array_unique($themes[$theme_key]);
}

/**
 * Return information from the .info file of a theme (and possible base themes).
 *
 * @param string $theme_key
 *   The machine name of the theme.
 * @param string $key
 *   The key name of the item to return from the .info file. This value can
 *   include "][" to automatically attempt to traverse any arrays.
 * @param bool $base_themes
 *   Recursively search base themes, defaults to TRUE.
 *
 * @return string|array|false
 *   A string or array depending on the type of value and if a base theme also
 *   contains the same $key, FALSE if no $key is found.
 */
function atomium_get_theme_info($theme_key = NULL, $key = NULL, $base_themes = TRUE) {
  // If no $theme_key is given, use the current theme if we can determine it.
  if (!isset($theme_key)) {
    $theme_key = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : FALSE;
  }
  if ($theme_key) {
    $themes = list_themes();
    if (!empty($themes[$theme_key])) {
      $theme = $themes[$theme_key];
      // If a key name was specified, return just that array.
      if ($key) {
        $value = FALSE;
        // Recursively add base theme values.
        if ($base_themes && isset($theme->base_themes)) {
          foreach (array_keys($theme->base_themes) as $base_theme) {
            $value = atomium_get_theme_info($base_theme, $key);
          }
        }
        if (!empty($themes[$theme_key])) {
          $info = $themes[$theme_key]->info;
          // Allow array traversal.
          $keys = explode('][', $key);
          foreach ($keys as $parent) {
            if (isset($info[$parent])) {
              $info = $info[$parent];
            }
            else {
              $info = FALSE;
            }
          }
          if (is_array($value)) {
            if (!empty($info)) {
              if (!is_array($info)) {
                $info = array($info);
              }
              $value = drupal_array_merge_deep($value, $info);
            }
          }
          else {
            if (!empty($info)) {
              if (empty($value)) {
                $value = $info;
              }
              else {
                if (!is_array($value)) {
                  $value = array($value);
                }
                if (!is_array($info)) {
                  $info = array($info);
                }
                $value = drupal_array_merge_deep($value, $info);
              }
            }
          }
        }
        return $value;
      }
      // If no info $key was specified, just return the entire info array.
      return $theme->info;
    }
  }
  return FALSE;
}

/**
 * Retrieves an element's "attributes" array.
 *
 * @param array $element
 *   The individual renderable array element. It is possible to also pass the
 *   $variables parameter in [pre]process functions and it will logically
 *   determine the correct path to that particular theme hook's attribute array.
 *   Passed by reference.
 * @param string $property
 *   Determines which attributes array to retrieve. By default, this is the
 *   normal attributes, but can be "wrapper_attributes" or
 *   "input_group_attributes".
 *
 * @return array
 *   The attributes array. Passed by reference.
 */
function &_atomium_get_attributes(array &$element, $property = 'attributes') {
  // Attempt to retrieve a renderable element attributes first.
  if (
    isset($element['#type']) ||
    isset($element['#theme']) ||
    isset($element['#pre_render']) ||
    isset($element['#markup']) ||
    isset($element['#theme_wrappers']) ||
    isset($element["#$property"])
  ) {
    if (!isset($element["#$property"])) {
      $element["#$property"] = array();
    }
    return $element["#$property"];
  }
  // Treat $element as if it were a [pre]process function $variables parameter
  // and look for a renderable "element".
  elseif (isset($element['element'])) {
    if (!isset($element['element']["#$property"])) {
      $element['element']["#$property"] = array();
    }
    return $element['element']["#$property"];
  }

  // If all else fails, create (if needed) a default "attributes" array. This
  // will, at the very least, either work or cause an error that can be tracked.
  if (!isset($element[$property])) {
    $element[$property] = array();
  }

  return $element[$property];
}

/**
 * Copy of the drupal_attributes function.
 *
 * The only difference is that if a key is a numeric, it will only display the
 * value. Ex: 0="data-closable" will be displayed: data-closable.
 */

/**
 * Copy of the drupal_attributes function.
 *
 * The only difference is that if a key is a numeric, it will only display the
 * value. Ex: 0="data-closable" will be displayed: data-closable.
 *
 * @param array $attributes
 *   The attributes array.
 * @param string $name
 *   The name of the key holding the attributes.
 * @param string $hook
 *   The hook being processed.
 *
 * @return string
 *   The attributes in a single string, cleaned.
 */
function atomium_drupal_attributes(array $attributes = array(), $name = NULL, $hook = NULL) {
  // Remove empty arrays and empty strings.
  $attributes = array_filter($attributes, function ($value) {
    if (!is_array($value)) {
      return (strlen($value) != 0);
    }
    return $value;
  });

  // If empty, just return an empty string.
  if (empty($attributes)) {
    return '';
  }

  $attributes = _atomium_clean_attributes($attributes, $name, $hook);
  return $attributes ? ' ' . implode(' ', $attributes) : '';
}

/**
 * Helper function to handle attributes cleaning.
 *
 * @param array $attributes
 *   An array of attributes.
 * @param string $name
 *   The name of the key holding the attributes.
 * @param string $hook
 *   The hook being processed.
 *
 * @return array
 *   The attributes cleaned.
 */
function _atomium_clean_attributes(array $attributes = array(), $name = NULL, $hook = NULL) {
  foreach ($attributes as $attribute => &$raw_data) {

    $data = array();
    foreach (new RecursiveIteratorIterator(new RecursiveArrayIterator(array($raw_data))) as $v) {
      $data[$v] = $v;
    }

    $data = array_filter($data,
      function ($item) {
        return strlen($item) != 0;
      }
    );

    $data = array_map(function ($item) use ($attribute, $hook) {
      if ('class' === $attribute) {
        // Disabled for now or else it breaks the javascript in the
        // filter tips component.
        if ('filter_guidelines' !== $hook) {
          $item = drupal_html_class($item);
        }
      }

      if ('placeholder' === $attribute) {
        $item = strip_tags($item);
      }

      if ('id' === $attribute) {
        // Disabled for now, it's causing issue in
        // admin/structure/views/settings.
        // $item = drupal_html_id($item);.
      }

      return trim(check_plain($item));
    }, $data);

    if ('class' == $attribute) {
      asort($data);
    }

    $data = implode(' ', $data);

    if (!is_numeric($attribute)) {
      $data = sprintf('%s="%s"', $attribute, $data);
    }

    $raw_data = $data;
  }

  asort($attributes);
  return $attributes;
}

/**
 * Discover templates based on directory name.
 *
 * It is important that directories have the name of the hook for the moment.
 */
function atomium_find_templates() {
  $templates = array();

  foreach (_atomium_get_base_themes(NULL, TRUE) as $theme) {
    $path = drupal_get_path('theme', $theme) . '/templates';
    if (is_dir($path)) {
      $directories = array_diff(scandir($path), array('..', '.'));
      foreach ($directories as $directory) {
        $templates[$theme][$directory] = array(
          'theme' => $theme,
          'directory' => $path . '/' . $directory,
        );
      }
    }
  }

  return $templates;
}

/**
 * Get list of component definitions.
 *
 * @return array
 *   List of definitions.
 */
function atomium_get_component_definitions() {
  $definitions = array();
  foreach (atomium_find_templates() as $theme => $theme_data) {
    foreach ($theme_data as $component => $component_data) {

      $file = sprintf('%s/%s.component.inc', $component_data['directory'], $component);
      if (file_exists($file)) {
        include_once $file;
      }

      $function_name = $theme . '_atomium_definition_' . $component;
      if (function_exists($function_name)) {
        $definition = call_user_func($function_name);

        // Prepend hash to all preview properties.
        foreach ($definition['preview'] as $key => $value) {
          if (!is_numeric($key)) {
            $definition['preview']["#{$key}"] = $value;
            unset($definition['preview'][$key]);
          }
        }

        // Handle preview differently whereas a component is an element or not.
        $element = element_info($component);
        if (!empty($element)) {
          $definition['preview'] = array_merge($element, $definition['preview']);
        }
        else {
          $definition['preview']['#theme'] = array($component);
        }

        $definitions[$component] = $definition;
      }
    }
  }
  return $definitions;
}

/**
 * Verbatim copy of drupal_get_breadcrumb().
 *
 * The only modified stuff are the call to menu_get_active_breadcrumb() which
 * is replaced with atomium_menu_get_active_breadcrumb().
 *
 * @see drupal_get_breadcrumb()
 */
function atomium_drupal_get_breadcrumb() {
  $breadcrumb = drupal_set_breadcrumb();

  if (!isset($breadcrumb)) {
    $breadcrumb = atomium_menu_get_active_breadcrumb();
  }

  return $breadcrumb;
}

/**
 * Verbatim copy of menu_get_active_breadcrumb().
 *
 * The difference with the original function is that this function returns
 * a render array instead of an array of links rendered.
 *
 * This will allow us to modify the data properly.
 *
 * @see menu_get_active_breadcrumb()
 */
function atomium_menu_get_active_breadcrumb() {
  $breadcrumb = array();

  // No breadcrumb for the front page.
  if (drupal_is_front_page()) {
    return $breadcrumb;
  }

  $item = menu_get_item();
  if (!empty($item['access'])) {
    $active_trail = menu_get_active_trail();

    // Allow modules to alter the breadcrumb, if possible, as that is much
    // faster than rebuilding an entirely new active trail.
    drupal_alter('menu_breadcrumb', $active_trail, $item);

    // Don't show a link to the current page in the breadcrumb trail.
    $end = end($active_trail);
    if ($item['href'] == $end['href']) {
      array_pop($active_trail);
    }

    // Remove the tab root (parent) if the current path links to its parent.
    // Normally, the tab root link is included in the breadcrumb, as soon as we
    // are on a local task or any other child link. However, if we are on a
    // default local task (e.g., node/%/view), then we do not want the tab root
    // link (e.g., node/%) to appear, as it would be identical to the current
    // page. Since this behavior also needs to work recursively (i.e., on
    // default local tasks of default local tasks), and since the last non-task
    // link in the trail is used as page title (see menu_get_active_title()),
    // this condition cannot be cleanly integrated into menu_get_active_trail().
    // menu_get_active_trail() already skips all links that link to their parent
    // (commonly MENU_DEFAULT_LOCAL_TASK). In order to also hide the parent link
    // itself, we always remove the last link in the trail, if the current
    // router item links to its parent.
    if (($item['type'] & MENU_LINKS_TO_PARENT) == MENU_LINKS_TO_PARENT) {
      array_pop($active_trail);
    }

    foreach ($active_trail as $parent) {
      $breadcrumb[] = array(
        '#theme' => array('link'),
        '#text' => $parent['title'],
        '#path' => $parent['href'],
        '#options' => $parent['localized_options'],
      );
    }
  }
  return $breadcrumb;
}

/**
 * Custom utility callback that apply to each array element, a callback.
 *
 * Unlike array_walk_recursive, this function send the key name if a value is
 * an array.
 * As the value is passed by reference, you are able to modify its value within
 * the callback.
 *
 * @param array $array
 *   The array.
 * @param callable $callback
 *   The callback function.
 */
function atomium_recursive_foreach(array &$array, callable $callback) {
  $array['#processed'] = TRUE;
  foreach ($array as $key => &$value) {
    if (is_array($value) && !isset($value['#processed'])) {
      atomium_recursive_foreach($value, $callback);
    }
    call_user_func_array($callback, array($key, &$value, &$array));
  }
  unset($array['#processed']);
}
