<?php
/**
 * @file
 * Display page for services state.
 */

/**
 * Implements hook_menu().
 */
function servicestate_view_page() {
  $content = array();

  // Call from cache here

  // call hook module here

  // Sort by group, weight, title

  // output to call by ajax - somehow

  $content['title'] = array('#type' => 'markup', '#markup' => 'This is dummy content');

  $content['table'] = array(
    '#theme' => 'servicestate_view_table',
    '#elements' => array(),
  );

  $services = servicestate_get_services();
  foreach ($services as $service => $data) {
    if (!$data['enabled']) {
      continue;
    }
    $content['table']['#elements'][] = array(
      '#theme' => 'servicestate_view_item',
      '#service' => $service,
      '#data'    => $data,
      '#method'  => 'ajax',
    );
  }

  return $content;
}
