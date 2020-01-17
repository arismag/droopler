<?php

/**
 * @file
 * Contains \Drupal\d_update\ConfigCompare.
 */

namespace Drupal\d_update;

/**
 * Config Compare service.
 *
 * @package Drupal\d_update
 */
class ConfigCompare {

  /**
   * Generates hash for the specified config.
   *
   * @param string $config_name
   *   Full name of the config, eg node.type.content_page.
   *
   * @return bool|string
   *   Returns hash or false if there is no config with provided name.
   */
  public function generateHashFromDatabase($config_name) {
    $config = \Drupal::config($config_name)->getRawData();
    if (empty($config)) {
      return FALSE;
    }

    unset($config['uuid']);
    unset($config['lang']);
    unset($config['langcode']);
    unset($config['_core']);
    $config_string = serialize($config);

    return md5($config_string);
  }

  /**
   * Compares config name hash wit provided hash.
   *
   * @param string $config_name
   *   Full name of the config, eg node.type.content_page.
   * @param string $hash
   *   Optional argument with hash.
   *
   * @return bool
   *   Returns true if hashes are the same or hash was not provided, false on
   *   different hashes.
   */
  public function compare($config_name, $hash = NULL) {
    if (empty($hash)) {
      return TRUE;
    }
    else {
      return $this->generateHashFromDatabase($config_name) == $hash;
    }
  }

  /**
   * Generates hashes from config array, saves hashes into file.
   *
   * @param array $configs
   *   Array of configs.
   * @param string $filename
   *   Filename to save config under without extension.
   */
  public function massProduceHashes(array $configs, string $filename) {
    $file = fopen('/app/app/' . $filename . '.txt', 'w');
    fwrite($file, '[');
    foreach ($configs as $moduleName => $moduleConfigs) {
      fwrite($file, "'" . $moduleName . "' => [");
      foreach ($moduleConfigs as $configName => $arrayHash) {
        $newHash = $this->generateHashFromDatabase($configName);
        fwrite($file, "'" . $configName . "' =>'" . $newHash . "',");
      }
      fwrite($file, '],');
    }
    fwrite($file, '];');
    fclose($file);
  }
}
