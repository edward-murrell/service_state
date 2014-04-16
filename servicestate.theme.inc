<?php
/**
 * @file
 * Theme preprocess file for Service state.
 */

/*
 * Implements hook_preprocess_HOOK()
 * Renders the children of the servicestate table
 */
function servicestate_preprocess_servicestate_view_table(&$variables) {
    $variables['children'] = drupal_render_children($variables['elements']);
}

/*
 * Implements hook_preprocess_HOOK()
 * Renders the children of the servicestate table
 */
function servicestate_preprocess_servicestate_view_item(&$variables) {
  // Do we even need this function?

  //$variables['foobar']    = 'x';

  //dd($variables);
}
