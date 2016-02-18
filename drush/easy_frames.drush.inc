<?php
/**
 * @file
 * drush integration for cropper.
 */

/**
 * The Cropper plugin URI.
 */
define('CROPPER_DOWNLOAD_URI', 'https://github.com/fengyuanchen/cropper/archive/master.zip');

/**
 * Implements hook_drush_command().
 *
 * For a list of recognized keys
 * @See drush_parse_command()
 */
function easy_frames_drush_command() {

  $items = array();

  $items['cropper-download'] = array(
    'callback'    => '_cropper_drush_download_cropper',
    'description' => dt('Downloads the Cropper library from authors github.com repository.'),
    'options' => array(
      'path' => dt('Optional. The path to the download folder. If omitted, Drush will use the default location (sites/all/libraries/cropper).'),
    ),
    'aliases'     => array('cropperdl'),
  );

  return $items;

}

/**
 * Implements hook_drush_help().
 */
function easy_frames_drush_help($section) {
  switch ($section) {
    case 'drush:cropper-download':
      return dt("Downloads the Cropper library from authors github.com repository. Accepts an optional destination argument.");
  }
}

/**
 * Helper function downloads Cropper plugin.
 */
function _cropper_drush_download_cropper() {

  // Get the path from the argument, if site, or use the default.
  $drush_context = drush_get_context('DRUSH_DRUPAL_ROOT');

  // Can we use Libraries API?
  if (module_exists('libraries') && function_exists('libraries_get_path')) {
    $libraries_dir = libraries_get_path('cropper');
  }

  // Load the path.
  $path = $libraries_dir ? $drush_context . '/' . $libraries_dir : $drush_context . '/sites/all/libraries/cropper';

  $path = drush_get_option('path', $path);

  drush_log(dt('Download destination path: "@path"', array('@path' => $path)), 'notice');

  // Set the directory to the download location.
  $olddir = getcwd();

  $download_path = str_replace('/cropper', '', $path);

  chdir($download_path);

  $download_uri = CROPPER_DOWNLOAD_URI;

  // Download the zip archive.
  if ($filepath = drush_download_file($download_uri, $download_path . '/  master.zip')) {
    $filename = basename($filepath);
    $dirname =  'cropper-master';

    // Remove any existing Cropper plugin directory.
    if (is_dir($dirname) || is_dir('cropper')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('cropper', TRUE);
      drush_log(dt('A existing Cropper plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    drush_tarball_extract($filename);

    // Change the directory name to "select2" if needed.
    if ($dirname != 'cropper') {
      drush_move_dir($dirname, 'cropper', TRUE);
      $dirname = 'cropper';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('Cropper plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the Cropper plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);

}
