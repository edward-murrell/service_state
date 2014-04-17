<tr class="<?php print implode(' ', $variables['classes_array']); ?>" id="<?php print SERVICESTATE_ID_PREFIX.'-'.$service; ?>">
  <td class="servicestate-table-title">
    <?php print $title; ?>
  </td>
  <td class="servicestate-table-state">
    <?php
      // TODO, consider cleaning this up
      if ($state['status'] == SERVICESTATE_OK) {
        print "OK";
      } else {
        print $state['error'];
      }
    ?>
  </td>
  <td class="servicestate-table-update">
    <?php print $button; ?>
  </td>
</tr>