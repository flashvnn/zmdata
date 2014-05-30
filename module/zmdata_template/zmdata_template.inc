<?php

/**
 * Clear up string.
 */
function zmdata_template_cleanup($str) {
  return trim(preg_replace("/\s*(?:\*\/|\?>).*/", '', $str));
}

/**
 * Get avaiables templates.
 *
 * @return array
 *   List of Field formatter template.
 */
function zmdata_template_get_templates() {
  static $page_templates = array();
  if (empty($page_templates)) {
    $theme_default = $GLOBALS['conf']['theme_default'];
    $theme_path = drupal_get_path('theme', $theme_default);
    $files = file_scan_directory($theme_path, '/^page--.*\.tpl\.php$/');
    foreach ($files as $full_path => $file) {
      $file_content = file_get_contents($full_path);
      $header = array();
      if (!preg_match('|Template Name:(.*)$|mi', $file_content, $header)) {
        continue;
      }
      $template_file = str_replace($theme_path . "/", '', $file->filename);
      $template_file = str_replace('.tpl.php', '', $template_file);
      $template_file = str_replace('--', '__', $template_file);
      $page_templates[$template_file] = zmdata_template_cleanup($header[1]);
    }
  }

  return $page_templates;
}
