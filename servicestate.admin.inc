<?php
/**
 * @file
 * Administration pages and forms for servicestate module
 */

/**
 * Main page for service state administration. Currently wraps a form.
 */
function servicestate_admin_page() {
  drupal_add_css(__DIR__ . '/css/servicestate.css');
  return array(
    'admin_form' => drupal_get_form('servicestate_admin_form'),
  );
}

/**
 * System settings form for service state
 */
function servicestate_admin_form($form, &$form_state) {
  $form = array();
  $form['servicestate_page_link'] = array(
    '#type'       => 'link',
    '#title'      => t('Service state list'),
    '#href'       => 'servicestate',
    '#attributes' => array(
      'class' => (
          'admin-to-page-link'
        )
    ),
  );
  $form['servicestate_error_field'] = array(
    '#type' => 'radios',
    '#title' => t('Error fields as messages'),
    '#default_value' => variable_get('servicestate_error_field', SERVICESTATE_ERROR_FIELD_ERROR),
    '#description' => t('How should error messages rendered when query via JSON or XML. The default is to have these as a field called \'error\', if set to message, then \'error\' fields will have the key \'message\' instead.'),
    '#required' => FALSE,
    '#options' => array(
      SERVICESTATE_ERROR_FIELD_ERROR => 'error (default)',
      SERVICESTATE_ERROR_FIELD_MESSAGE => 'message',
    ),
  );
  return system_settings_form($form);
}
