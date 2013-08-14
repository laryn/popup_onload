<?php

/**
 * @file
 * Administrative interface callbacks of the Popup Ad module.
 */

/**
 * Popup add/edit form.
 */
function popupad_form($form, &$form_state, $popupad, $op = 'edit') {

  if ($op == 'clone') {
    $popupad->name .= ' (cloned)';
  }

  $form['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $popupad->name,
    '#description' => t('The human-readable name of the popup.'),
    '#required' => TRUE,
  );

  $form['body'] = array(
    '#title' => t('Popup content'),
    '#type' => 'text_format',
    '#default_value' => $popupad->body,
    '#description' => t('The content of the popup.'),
    '#required' => TRUE,
    '#format' => $popupad->format,
  );

  $form['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#default_value' => $popupad->width,
    '#description' => t('The width of the popup, given in pixels. "0" defaults to auto-detection.'),
    '#required' => TRUE,
  );

  $form['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $popupad->height,
    '#description' => t('The height of the popup, given in pixels. "0" defaults to auto-detection.'),
    '#required' => TRUE,
  );

  $form['fixed_position'] = array(
    '#title' => t('Fixed position'),
    '#type' => 'checkbox',
    '#default_value' => $popupad->fixed_position,
    '#description' => t('Whether the popup is fixed in the browser window.'),
  );

  $form_state['popupad'] = $popupad;
  field_attach_form('popupad', $popupad, $form, $form_state);

  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
  );

  return $form;
}

/**
 * Submit callback for the popup form.
 */
function popupad_form_submit(&$form, &$form_state) {
  $popupad = entity_ui_controller('popupad')->entityFormSubmitBuildEntity($form, $form_state);
  // Save and go back.
  $popupad->save();
  $form_state['redirect'] = 'admin/structure/popupad';
}

/**
 * Popup Ad admin settings form.
 */
function popupad_admin_settings_form($form, &$form_state) {
  // Check if colorbox library is installed.
  $library_colorbox = libraries_detect('colorbox');

  if (!$library_colorbox['installed']) {
    $error_message = $library_colorbox['error message'];
    $error_message .= '<br />' .
      t('You can download the colorbox library !here',
        array('!here' => l(t('here'), $library_colorbox['download url'])));
    drupal_set_message($error_message, 'error', FALSE);
  }

  // Create the list of all sorting methods to be used in the form.
  $methods = popupad_sort_methods();

  $form['sort_methods'] = array(
    '#type' => 'fieldset',
    '#title' => t('Popup sort methods'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('How to determine the popup, displayed to the user.'),
  );

  $form['sort_methods'][POPUPAD_VAR_SORT_METHOD] = array(
    '#type' => 'radios',
    '#options' => $methods,
    '#default_value' => variable_get(POPUPAD_VAR_SORT_METHOD, POPUPAD_DEFAULT_SORT_METHOD),
  );

  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Miscellaneous'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#description' => t('Misc settings.'),
  );

  $form['misc'][POPUPAD_VAR_COOKIE_LIFETIME] = array(
    '#type' => 'textfield',
    '#title' => t('Popup cookie lifetime'),
    '#description' => t('How many days popups will not be displayed to the user after the first display.'),
    '#default_value' => variable_get(POPUPAD_VAR_COOKIE_LIFETIME, POPUPAD_DEFAULT_COOKIE_LIFETIME),
  );

  $form['misc'][POPUPAD_VAR_DISPLAY_DELAY] = array(
    '#type' => 'textfield',
    '#title' => t('Popup display delay'),
    '#description' => t('Delay in milliseconds before the popup is displayed to the user.'),
    '#default_value' => variable_get(POPUPAD_VAR_DISPLAY_DELAY, POPUPAD_DEFAULT_DELAY),
  );

  $form['misc'][POPUPAD_VAR_USE_RULES] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable normal popup processing'),
    '#description' => t('If set, popupad module will stay enabled, but popup display will be invoked only as a Rules module action.'),
    '#default_value' => variable_get(POPUPAD_VAR_USE_RULES, FALSE),
  );

  $form['misc'][POPUPAD_VAR_INCLUDE_PATHS] = array(
    '#type' => 'textarea',
    '#title' => t('Display only at specified paths'),
    '#description' => t('Specify pages by using their paths. Enter one path per line. Use the "*" character as a wildcard. Leave empty to include all pages, except admin ones. %front is the front page.', array('%front' => '<front>')),
    '#default_value' => variable_get(POPUPAD_VAR_INCLUDE_PATHS, ''),
  );

  return system_settings_form($form);
}

/**
 * Popup Ad admin settings form validation callback.
 */
function popupad_admin_settings_form_validate($form, &$form_state) {
  $numeric_values = array(
    POPUPAD_VAR_COOKIE_LIFETIME,
    POPUPAD_VAR_DISPLAY_DELAY,
  );
  foreach ($numeric_values as $form_field) {
    if (!is_numeric($form_state['values'][$form_field])) {
      form_set_error($form_field, t('Please specify numeric value.'));
    }
  }
}
