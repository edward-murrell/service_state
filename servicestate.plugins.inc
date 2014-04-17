<?php
/**
 * @file
 * File of functions for querying other services.
 */

// Memcache

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

