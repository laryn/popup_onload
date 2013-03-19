<?php

/**
 * @file
 * Hooks provided by the Popup Ad module.
 */

/**
 * Provide sort methods for popups.
 *
 * Must return an array of 'callback' => 'human readable name' pairs.
 * Each callback must return a single popup, which will be displayed.
 *
 * @see popupad_sort_methods()
 */
function hook_popupad_sort_methods() {
  return array(
    'mymodule_callback' => t('Sort method'),
  );
}

/**
 * Check popup display conditions.
 *
 * Should return TRUE or FALSE. If at least one FALSE value is returned
 * from any module, popup is not displayed.
 *
 * @see popupad_check_display_conditions()
 */
function hook_popupad_check_display_conditions($popupad) {
  return !popupad_check_time_cookie();
}

/**
 * Alter colorbox JS settings right before the popup is displayed.
 */
function hook_popupad_js_settings_alter(&$popup_settings, &$popupad) {
  // Disable closing popup colorbox on 'esc' key press.
  $popup_settings['escKey'] = FALSE;
}
