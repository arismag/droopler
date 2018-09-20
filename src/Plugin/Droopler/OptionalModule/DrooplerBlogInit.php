<?php

namespace Drupal\droopler\Plugin\Droopler\OptionalModule;

/**
 * Droopler blog init.
 *
 * @DrooplerOptionalModule(
 *   id = "d_blog_init",
 *   label = @Translation("Enable Blog init"),
 *   type = "module",
 *   dependencies = {
 *    "d_blog",
 *   },
 *   standardlyEnabled = 1,
 * )
 */
class DrooplerBlogInit extends AbstractOptionalModule {}
