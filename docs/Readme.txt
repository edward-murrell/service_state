ServiceState
------------

States
------
The normal states are as follows:

OK      - Everything is normal.
WARN    - Attention is needed, but is not critical. eg; Low disk space.
FAIL    - Something is broken. eg; Database does not respond.
MESSAGE - Provides information, such as a label, environment.

Special states:
nosuchservice - This service does not exist.
DISABLED      - The service exists, but is not enabled.
INTERROR      - Internal error in the check system, such as a PHP error.

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

Writing callbacks
-----------------

Callbacks need to return an array in one of the following structures
array(
 'status' => SERVICESTATE_OK | SERVICESTATE_MESSAGE,
 'message' => 'Messages goes here'
)
OR
array(
 'status' => SERVICESTATE_WARN | SERVICESTATE_FAIL,
 'error'  => 'Error / warn status goes here'
)

Special functions
-----------------

These functions are useful for returning SERVICESTATE_MESSAGE data.

function servicestate_message_function($function)
function servicestate_message_variable($variable)
