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

  // Sort by group, weight, title

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
