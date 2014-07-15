ServiceState
------------

Writing tests
-------------
Implement a hook_servicestate_services in your module.

The array key is the machine name of the service. This will show up as the
name used to query via ajax and JSON.

Below is an example of a service state.

/*
 * Implements hook_servicestate_services
 */
function MYMODULE_servicestate_services() {
  $services = array();
  $services['water_levels'] = array(
    'title'         => t('Tank levels'),
    'description'   => t('Checks the level of water isn't too low.'),
    'callback'      => 'MYMODULE_function_to_call',
    'arguments'     => array('All tanks',200),
    'file'          => 'servicestate.plugins.inc',
    'group'         => 'Tank levels',
    'weight'        => 5,
    'enabled'       => TRUE,
  );
  return $services;
}

* title         - Short natural language name of service.
* description   - Long natural language description of the service.
* callback      - The function name to call that returns the current state
                  of the service.
* arguments     - function arguments to pass to the function indicated in
                  callback above.
* file          - File to load before running function indicated in callback
                  above. Usually this file contains the callback function.
* group         - Plain text group used to sort services.
* weight        - Weight to sort services by, this is secondary to group.
* enabled       - Indicates that the service is available and is checked.