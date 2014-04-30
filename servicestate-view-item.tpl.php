<tr class="<?php print implode(' ', $variables['classes_array']); ?>" id="<?php print SERVICESTATE_ID_PREFIX.'-'.$service; ?>">
  <td class="servicestate-table-title">
    <?php print $title; ?>
  </td>
  <td class="servicestate-table-state">
    <?php
      // TODO, consider cleaning this up
      if ($state['status'] == SERVICESTATE_OK) {
        print "OK";
        print ' - ';
        print $state['message'];
      } else if ($state['status'] == SERVICESTATE_MESSAGE) {
        print $state['message'];
      } else {
        print $state['error'];
      }
    ?>
  </td>
  <td class="servicestate-table-update">
    <?php print $button; ?>
  </td>
  <td class="servicestate-table-json-link">
    <?php print $json_link; ?>
  </td>
</tr>