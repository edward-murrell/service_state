<div class="<?php print implode(' ', $variables['classes_array']); ?>">
<table>
  <thead>
    <tr>
      <th class="servicestate-table-state">Service</th>
      <th class="servicestate-table-state">State</th>
      <th class="servicestate-table-update"></th>
    </tr>
  </thead>
  <tbody><?php print $children; ?></tbody>
</table>