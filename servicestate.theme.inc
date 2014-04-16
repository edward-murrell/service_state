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
 * Renders the children of the servicestate table.
 * $variable paramters:
 *  service - service name, required
 *  data    - optional prefilled data selection - will be filled
 *            automatically from service if empty. Worth using if the
 *            data is already available.
 *  state   - optional prefilled state data - if empty, the normal
 *            method of retrieving data specified in the data array
 *            will be used.
 *  method  - string of 'html' or 'ajax', html is not reccomended, as
 *            upstream services may time out.
 */
function servicestate_preprocess_servicestate_view_item(&$variables) {
  // TODO: If ajax here, create a container and callback, and skip the rest

  // Fill out the data variable if empty
  if (empty($variables['data'])) {
    $services = servicestate_dummy_services();
    if (!array_key_exists($variables['service'],$services)) {
      return ''; // TODO: Change this to a sane error.
    } else {
      $variables['data'] = $services['data'];
    }
  }
  if (empty($variables['state'])) {
    $variables['state'] = servicestate_query_callback($variables['service']);
  }

  if (!isset($variables['title'])) {
    $variables['title'] = $variables['data']['title'];
  }
}
