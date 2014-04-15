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

  $services = servicestate_dummy_services();
  foreach ($services as $service => $data) {
    $content[$service] = array('#type' => 'markup', '#markup' => "<h2>{$data['title']}</h2>");
    
    // Create template here.    
  }
  return $content;
}
