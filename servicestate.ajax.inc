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



/*
 * Render the status callback as a raw json url.
 * @param $id the machine name of the service.
 */
function servicestate_json_ajax($id) {
  $services = servicestate_get_services();
  if (!array_key_exists($id,$services)) {
    $state = array(
      'status' => SERVICESTATE_NO_SUCH_SERVICE,
      'error'  => 'This service does not exist',
    );
  } else {
    $srv  = $services[$id];
    $state = servicestate_query_callback($id);
  }
  $error_key = variable_get('servicestate_error_field', SERVICESTATE_ERROR_FIELD_ERROR);
  if (array_key_exists('error',$state) && $error_key != 'error') {
    $state[$error_key] = $state['error'];
    unset($state['error']);
  }

  print drupal_json_output($state);
  exit();
}
