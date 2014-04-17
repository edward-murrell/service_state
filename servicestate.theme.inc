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
  // TODO: Cache this.
  $services = servicestate_get_services();

  // Fill out the data variable if empty
  if (empty($variables['data'])) {
    if (!array_key_exists($variables['service'],$services)) {
      return ''; // TODO: Change this to a sane error.
    } else {
      $variables['data'] = $services[$variables['service']];
    }
  }

  if (empty($variables['title'])) {
    $variables['title'] = $variables['data']['title'];
  }

  // If method is ajax
  if ($variables['method'] == 'ajax' && array_key_exists($variables['service'],$services)) {
    drupal_add_library('system', 'drupal.ajax');

    // TODO change link to update to code that automatically calls ajax on load
    $variables['title'] = $variables['data']['title'];
    $variables['state'] = '?'; // TODO : Change this to a spinner.
  }

  $variables['button'] =
    l('Update',
      "servicestate/nojs/{$variables['service']}",
       array(
        'attributes' => array(
          'id' => 'servicestate-item-'.$variables['service'],
          'class' => array('use-ajax'),
      )
    )
  );

  if (empty($variables['state'])) {
    $variables['state'] = servicestate_query_callback($variables['service']);
  }
}
