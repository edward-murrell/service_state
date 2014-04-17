<?php
/**
 * @file
 * Ajax functions for Service State module.
 */

/*
 * Render the status callback, and return as Drupal ajax.
 * @param $id the machine name of the service.
 */
function servicestate_drupal_ajax($id) {
  $services = servicestate_get_services();
  if (!array_key_exists($id,$services)) {  
    return '';
  } else {
    $srv  = $services[$id];
    $data = servicestate_get_services($id);
  }
  
  $selector = '#'.SERVICESTATE_ID_PREFIX.'-'.$id;
  $item = array(
    '#theme' => 'servicestate_view_item',
    '#service' => $id,
    '#method'  => 'html',
  );
  $output = drupal_render($item);

  $commands = array();
  $commands[] = ajax_command_replace(
    $selector,
    $output
  );

  // TODO: Check if this is the best/right way.
  print ajax_render($commands);
  exit();  
}
