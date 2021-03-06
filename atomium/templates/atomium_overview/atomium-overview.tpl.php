<?php

/**
 * @file
 * Contains template file.
 */
?>

<ul>
  <?php foreach ($definitions as $name => $definition): ?>
    <li>
      <a href="#<?php print $name?>"><?php print $definition['label'] ?></a>
    </li>
  <?php endforeach; ?>
</ul>

<h3><?php print t('Components') ?></h3>

<div>
  <?php foreach ($definitions as $name => $definition): ?>
    <a name="<?php print $name?>"></a>
    <h4><?php print $definition['label'] ?></h4>
    <fieldset>
      <legend><?php print t('Preview') ?></legend>
      <div>
        <p><?php print $definition['description'] ?></p>
        <div class="clearfix">
          <?php print render($definition['preview']) ?>
        </div>
      </div>
    </fieldset>
  <?php endforeach; ?>
</div>
