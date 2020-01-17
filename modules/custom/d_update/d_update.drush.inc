<?php

/**
 * @file
 * File declaring drush commands.
 */

/**
 * Implements hook_drush_command().
 */
function d_update_drush_command() {
  $commands['generate-config-hash'] = [
    'description' => 'Generates hash for entered config',
    'aliases' => ['gch'],
    'options' => [
      'config' => 'Config name',
    ],
    'examples' => [
      'drush gch node.type.content_page' => 'Generates hash for node type article',
    ],
  ];
  $commands['mass-generate-config-hash'] = [
    'description' => 'Generates hash for hardcoded config lists in form of PHP array',
    'aliases' => ['mgch'],
    'options' => [
      'result-file' => 'Name of the result file without extension',
    ],
  ];

  return $commands;
}

/**
 * Drush command logic for generating config hash.
 */
function drush_d_update_generate_config_hash($opt = NULL) {
  $check = \Drupal::hasService('d_update.config_compare');
  if ($check == FALSE) {
    drush_print(dt('Service to generate hash is missing.'));
    return;
  }
  $hash = \Drupal::service('d_update.config_compare')
    ->generateHashFromDatabase($opt);
  drush_print(dt('Hash for config @opt: ' . $hash, ['@opt' => $opt]));
}

/**
 * Drush command for generating file with array of hashes from config list.
 */
function drush_d_update_mass_generate_config_hash($opt = NULL) {
  $configs = [
    'd_content' => [
      'field.field.node.content_page.field_page_section' => '9a1690fe15a13fa505af05b76e793b70',
    ],
    'd_p_banner' => [
      'field.field.paragraph.d_p_banner.field_d_cta_link' => 'a145eaef534859402221c448fd67e3bc',
    ],
    'd_p_side_image' => [
      'field.storage.paragraph.field_d_p_si_image_side' => 'b6ac0addaabfecabe01727c888703ec0',
      'field.field.paragraph.d_p_side_image.field_d_cta_link' => '1c2228d6bc04287c678335082ad90dd6',
    ],
    'd_p_side_embed' => [
      'field.field.paragraph.d_p_side_embed.field_d_cta_link' => '0be7fbc269f875d507f92dcac8962937',
    ],
    'd_p_side_tiles' => [
      'field.field.paragraph.d_p_side_tiles.field_d_cta_link' => '20cf110a5b5ecb2304b9b68a11d7099c',
    ],
    'd_p_text_blocks' => [
      'field.field.paragraph.d_p_group_of_text_blocks.field_d_p_tb_block_reference' => '97dd017b20ad8add96ea20e13bbdea39',
      'field.field.paragraph.d_p_group_of_text_blocks.field_d_cta_link' => '12e9dbc1863b7bddb7cb6632b1a6d361',
    ],
    'd_p_text_paged' => [
      'field.field.paragraph.d_p_text_paged.field_d_cta_link' => 'ffda0c55cb64b91f1109971f67185970',
    ],
    'd_p_text_with_bckg' => [
      'field.field.paragraph.d_p_text_with_bckg.field_d_cta_link' => '27dca2ddd6b10a8cff0ec8c787c3dd9f',
    ],
  ];
  $check = \Drupal::hasService('d_update.config_compare');
  if ($check == FALSE) {
    drush_print(dt('Service to generate hash is missing.'));
    return;
  }

  $filename = drush_get_option('result-file');

  \Drupal::service('d_update.config_compare')
    ->massProduceHashes($configs, empty($filename) ? 'massHashes' : $filename);
  drush_print(dt('DONE'));
}
