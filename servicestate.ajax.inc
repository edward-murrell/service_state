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
  $services = servicestate_dummy_services();
  if (!array_key_exists($id,$services)) {  
    return '';
  } else {
    $srv  = $services[$id];
    $data = servicestate_query_callback($id);
  }
  $vars = array(
    'title' => $srv['title'],
    'state' => 'OK',
  );
  
  $commands = array();
  $commands[] = ajax_command_replace(
    '#block-oua-webservices-oua-courses-completed', // Selector to replace
    '<div id="block-oua-webservices-oua-courses-completed" class="block block-oua-webservices contextual-links-region no-title">' .
    render(_block_get_renderable_array(_block_render_blocks(array(block_load('o2s_webservices', 'oua_courses_completed'))))) .
    '</div>'
  );
  #$commands[] = ajax_command_invoke('#quicktabs-tab-oua_dashboard_subjects2-1', 'html', $args);

  print ajax_render($commands);
  exit();  
  
  
  // return render ajax array
}
