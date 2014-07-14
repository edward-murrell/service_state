<?php
/**
 * @file
 * File of functions for querying other services.
 */

/*
 * Check if memcache servers are alive.
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
    $live_servers = array();
    $dead_servers = array();

    $memcache_servers = array_keys(variable_get('memcache_servers', array('127.0.0.1:11211' => 'default')));
    foreach ($memcache_servers as $server) {
      list($m_host,$m_port) = explode(':', $server);
      $memcache = new Memcache();
      if ( $memcache->connect($m_host, $m_port) ) {
        $live_servers[] = $server;
      } else {
        $dead_servers[] = $server;
      }
    }

    if (empty($dead_servers)) {
      $state['status']  = SERVICESTATE_OK;
      $state['message'] = t('Memcache service is alive.');
    } else if (!empty($dead_servers) && !empty($live_servers)) {
      $state['status']  = SERVICESTATE_WARN;
      $state['error']   = t('Failed to connect to some memcache servers: '. implode(', ', $dead_servers));
    } else {
      $state['status']  = SERVICESTATE_FAIL;
      $state['error']   = t('Failed to connect to all memcache servers: '. implode(', ', $dead_servers));
    }
  }

  return $state;
}

/*
 * Returns list of memcache servers.
 */
function servicestate_memcache_list() {
  $memcache_servers = array_keys(variable_get('memcache_servers', array('127.0.0.1:11211' => 'default')));
  return array(
    'status'  => SERVICESTATE_MESSAGE,
    'message' => implode(', ', $memcache_servers),
  );
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
    $state['error'] = t('Cron has never been run.');
  }
  else if ($now-$failure > $last) {
    $state['status']  = SERVICESTATE_FAIL;
    $state['error']   = t('Cron last run !n minutes ago.', array('!n' => $last_run));
  }
  else if ($now-$warning > $last) {
    $state['status']  = SERVICESTATE_WARN;
    $state['error']   = t('Cron last run !n minutes ago.', array('!n' => $last_run));
  }
  else {
    $state['status']  = SERVICESTATE_OK;
    $state['message']   = t('Cron last run !n minutes ago.', array('!n' => $last_run));
  }
  return $state;
}

/*
 * Return the default database host.
 */
function servicestate_db_host() {
  global $databases;
  if (isset($databases['default']['default']['host']) && !empty($databases['default']['default']['host'])) {
    $state['status']  = SERVICESTATE_MESSAGE;
    $state['message'] = $databases['default']['default']['host'];
  } else {
    $state['status']  = SERVICESTATE_MESSAGE;
    $state['message'] = 'localhost';
  }
  return $state;
}

