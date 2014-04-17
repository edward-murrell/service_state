<div class="<?php print implode(' ', $variables['classes_array']); ?>" id="<?php print SERVICESTATE_ID_PREFIX.'-'.$service; ?>">
  <div>
    <?php print $title; ?>
  </div>
  <div>
    <?php
      // TODO, consider cleaning this up
      if ($state['status'] == SERVICESTATE_OK) {
        print "OK";
      } else {
        print $state['error'];
      }
    ?>
  </div>
  <div>
    <?php print $button; ?>
  </div>
</div>