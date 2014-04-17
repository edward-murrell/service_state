<?php
/**
 * @file
 * File of functions for querying other services.
 */

/*
 * Custom cron check
 * @param $timeout  - time in milliseconds before timing out connection to memcache
 */
function servicestate_memcache_check($timeout = 1500) {
  $state = array();

  // Check if memcache exists.
  if (!module_exists('memcache')) {
    watchdog('servicestate',t('Skipping service state check on memcache - memcache module is not enabled.'), array(), WATCHDOG_ERROR);    
    $state['status']  = SERVICESTATE_NO_SUCH_SERVICE;
    $state['error']   = t('Memcache module is not installed/enabled.');
  } else {
    // Replace this mess with a lock/set/get setting

    list($memcache_host) = explode(':', array_shift(array_keys(variable_get('memcache_servers', array('127.0.0.1:11211' => 'default')))));

    $memcache = new Memcache();

    if ( $memcache->connect($memcache_host, 11211) ) {
      $state['status']  = SERVICESTATE_OK;
      $state['message'] = t('Memcache service is alive.');
    } else {
      $state['status']  = SERVICESTATE_FAIL;
      $state['error']   = t('Failed to connecto to memcache service.');
    }
  }

  return $state;
}

/*
 * Custom cron check
 * @param warning  - time in minutes to change message to warning.
 * @param critical - time to change message to failure.
 */
function servicestate_cron_check($warning = 15, $failure = 90) {
  $last = variable_get('cron_last',0);
  $now  = time();

  $warning *= 60;
  $failure *= 60;

  $last_run = round(($now - $last)/60);

  $state = array();
  if ($last == 0) {
    $state['status']  = SERVICESTATE_WARN;
    $state['message'] = t('Cron has never been run.');
  }
  else if ($now-$failure > $last) {
    $state['status']  = SERVICESTATE_FAIL;
    $state['error']   = t('Cron last run %n minutes ago.', array('%n' => $last_run));
  }
  else if ($now-$warning > $last) {
    $state['status']  = SERVICESTATE_WARN;
    $state['error']   = t('Cron last run %n minutes ago.', array('%n' => $last_run));
  }
  else {
    $state['status']  = SERVICESTATE_OK;
    $state['error']   = t('Cron last run %n minutes ago.', array('%n' => $last_run));
  }
  return $state;
}

